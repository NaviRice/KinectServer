#include "navirice_image_distribution_server.h"
#include "navirice_ansi_codes.h"
#include "navirice_inet_util.h"
#include "navirice_image_impl.h"

#include "protobuf/navirice_image.pb.h"

#include <cerrno>
#include <cstring>
#include <clocale>

void navirice::ImageDistributionServer::handle_request(int cli_sock, sockaddr_in cli_addr){
	send_images(cli_sock, cli_addr);
	close(cli_sock);
}

void navirice::ImageDistributionServer::send_images(int cli_sock, sockaddr_in cli_addr){
	this->current_image_mutex.lock();
	std::string data = this->images.SerializeAsString();
	this->current_image_mutex.unlock();

#ifdef PRINT_LOG
	std::cout << this->get_prompt() + "sending images to " + int_to_ip(cli_addr.sin_addr.s_addr) + ":" + std::to_string(cli_addr.sin_port) + "\n";
#endif

	ssize_t n = write(cli_sock, data.c_str(), data.length());
	if(n < 0){
#ifdef PRINT_LOG
		std::cout << this->get_prompt() + ansi::red("WRITE ERROR") + " errno: " + std::strerror(errno) + " -- " + int_to_ip(cli_addr.sin_addr.s_addr) + ":" + std::to_string(cli_addr.sin_port) + "\n";
#endif	
	}

	data.clear();
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
		if (cli_sock >= 0){
			std::thread worker(&ImageDistributionServer::handle_request, this, cli_sock, cli_addr);
			worker.detach();
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

navirice::ImageSet_Image* naviriceImageToProtobuf(navirice::Image* img){
	if(img != NULL){	
		navirice::ImageSet_Image* proto_img = new navirice::ImageSet_Image();
		proto_img->set_width(img->width());
		proto_img->set_height(img->height());
		proto_img->set_channels(img->channels());
		proto_img->set_data_type(img->data_type() == navirice::ImageDataType::FLOAT ? navirice::ImageSet_Image_DataType_FLOAT:navirice::ImageSet_Image_DataType_UBYTE);
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
	std::cout << get_prompt() + "[" + ansi::yellow("setting new image") + "] -> Buffer Size: " + std::to_string(this->images.ByteSize()) + "\n"; 
#endif
	this->current_image_mutex.unlock();
}
