#include "navirice_image_distribution_server.h"
#include "navirice_ansi_codes.h"
#include "navirice_inet_util.h"
#include "navirice_image_impl.h"

#include "proto/navirice_image.pb.h"

#include <cerrno>
#include <cstring>
#include <clocale>

void navirice::ImageDistributionServer::handle_request(int cli_sock, sockaddr_in cli_addr){
	send_images(cli_sock, cli_addr);
	close(cli_sock);
}

void navirice::ImageDistributionServer::send_images(int cli_sock, sockaddr_in cli_addr){
	this->current_image_mutex.lock();
	uint64_t count = this->image_count;
	std::string data = this->images.SerializeAsString();
	this->current_image_mutex.unlock();
	ssize_t n;
	bool bypass = false;
	
	ProtoImageCount count_msg;
	count_msg.set_count(count);
	count_msg.set_byte_count(data.length());
	std::string count_msg_str = count_msg.SerializeAsString();
	n = write(cli_sock, count_msg_str.c_str(), count_msg_str.length());

	if(n < 0){
#ifdef PRINT_LOG
		std::cout << this->get_prompt() + ansi::red("WRITE ERROR 1") + " errno: " + std::strerror(errno) + " -- " + int_to_ip(cli_addr.sin_addr.s_addr) + ":" + std::to_string(cli_addr.sin_port) + "\n";
#endif
		bypass = true;
	}

	char read_buf[1024] = "";
	if(!bypass) n = read(cli_sock, read_buf, 1024);
	if(n < 0 && !bypass){
#ifdef PRINT_LOG
		std::cout << this->get_prompt() + ansi::red("READ ERROR") + " errno: " + std::strerror(errno) + " -- " + int_to_ip(cli_addr.sin_addr.s_addr) + ":" + std::to_string(cli_addr.sin_port) + "\n";
#endif
		bypass = true;
	}

	ProtoAcknowledge ack_msg;
	ack_msg.ParseFromArray(read_buf, n);
	if(ack_msg.state() != ProtoAcknowledge::CONTINUE){
#ifdef PRINT_LOG
		std::cout << this->get_prompt() + ansi::red("CONTINUE ERROR") + " -- " + int_to_ip(cli_addr.sin_addr.s_addr) + ":" + std::to_string(cli_addr.sin_port) + "\n";
#endif
		bypass = true;
	}

#ifdef PRINT_LOG
	if(!bypass)std::cout << this->get_prompt() + "sending images to " + int_to_ip(cli_addr.sin_addr.s_addr) + ":" + std::to_string(cli_addr.sin_port) + "\n";
#endif

	if(!bypass) n = write(cli_sock, data.c_str(), data.length());
	if(n < 0){
#ifdef PRINT_LOG
		std::cout << this->get_prompt() + ansi::red("WRITE ERROR 2") + " errno: " + std::strerror(errno) + " -- " + int_to_ip(cli_addr.sin_addr.s_addr) + ":" + std::to_string(cli_addr.sin_port) + "\n";
#endif
	}

}

void navirice::ImageDistributionServer::server_connection_listener(){
#ifdef PRINT_LOG
	std::cout << this->get_prompt() << ansi::green("Connection listener launched!") << std::endl;
#endif
	while(true){
		unsigned clilen;
		struct sockaddr_in cli_addr;
		clilen = sizeof(cli_addr);
		int cli_sock = accept(listener, (struct sockaddr *) &cli_addr, &clilen);

		struct timeval timeout;      
		timeout.tv_sec = 2;
		timeout.tv_usec = 0;

		if (cli_sock >= 0){	
			if (setsockopt (cli_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) >= 0){
				if (setsockopt (cli_sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) >= 0){
					std::thread worker(&ImageDistributionServer::handle_request, this, cli_sock, cli_addr);
					worker.detach();
				} else {
					close(cli_sock);
				}
			} else {
				close(cli_sock);
			}
		}

	}
}

std::string navirice::ImageDistributionServer::get_prompt(){
	return ansi::erase_line() + "-- IDServer | port: " + ansi::yellow(std::to_string(port)) + " |-> ";
}


navirice::ImageDistributionServer::ImageDistributionServer(uint16_t port){
	// current image lock for safety.
	current_image_mutex.lock();
	image_count = 0;

	this->port = port;
	memset((char*)&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
#ifdef PRINT_LOG
	std::cout << get_prompt() << "[" << ansi::blue("INITIALIZING") << "]" << std::flush;  
	usleep(500000);
#endif
	listener = socket(AF_INET, SOCK_STREAM, 0);		
	while(true){
		usleep(500000);
		if (bind(listener, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
			// failure
#ifdef PRINT_LOG
			std::cout << get_prompt() << "init: [" << ansi::red("FAILURE") << "] >> unbind the port! note: keep me alive" << std::flush; 
#endif
		}	else {
#ifdef PRINT_LOG
			std::cout << get_prompt() << "init: [" << ansi::green("SUCCESS") << "]" << std::endl; 
#endif
			break;
		}
	}
	listen(listener, 5);
	scl = new std::thread(&ImageDistributionServer::server_connection_listener, this);
	// DETACH AND FORGET!
	scl->detach();
	delete scl;

	// unlock 
	current_image_mutex.unlock();
}



navirice::ImageDistributionServer::~ImageDistributionServer(){
#ifdef PRINT_LOG
	std::cout << get_prompt() << "Shutting down server!" << std::endl; 
#endif
	// Close socket and mark it resuable
	close(listener);

#ifdef PRINT_LOG
	std::cout << get_prompt() << "[" << ansi::green("DONE") << "]" << std::endl; 
#endif	
}

navirice::ProtoImage* naviriceImageToProtobuf(navirice::Image* img){
	if(img != NULL){	
		navirice::ProtoImage* proto_img = new navirice::ProtoImage();
		proto_img->set_width(img->width());
		proto_img->set_height(img->height());
		proto_img->set_channels(img->channels());
		proto_img->set_data_type(img->data_type() == navirice::ImageDataType::FLOAT ? navirice::ProtoImage_DataType_FLOAT:navirice::ProtoImage_DataType_UBYTE);
		proto_img->set_data_size(img->get_raw_data_size());
		proto_img->set_data(std::string((char*)img->get_raw_data(), img->get_raw_data_size()));
		return proto_img;
	} else {
		return NULL;
	}
}

void navirice::ImageDistributionServer::set_new_images(Image* new_color_image, Image* new_ir_image, Image* new_depth_image){
	this->current_image_mutex.lock();
	this->image_count++;

	// POPULATE PROTOBUF
	this->images.Clear();
	this->images.set_count(this->image_count);
	this->images.set_allocated_rgb(naviriceImageToProtobuf(new_color_image));
	this->images.set_allocated_depth(naviriceImageToProtobuf(new_depth_image));
	this->images.set_allocated_ir(naviriceImageToProtobuf(new_ir_image));
#ifdef PRINT_LOG
	std::cout << get_prompt() + "[" + ansi::yellow("setting new image " + std::to_string(image_count)) + "] -> Buffer Size: " + std::to_string(this->images.ByteSize()) + "\n"; 
#endif
	this->current_image_mutex.unlock();
}
