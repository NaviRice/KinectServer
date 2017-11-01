#include <iostream>
#include <cstdlib>
#include <signal.h>

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>

#include "src/navirice.h"

using namespace std;
bool keep_alive = true;

#define PORT 29000

navirice::ImageDistributionServer* server;

void finish_program(int input){
	keep_alive = false;
}

class IOCW;

int main(int argc, char* argv[]){

	// KINNECT CONFIG
	libfreenect2::setGlobalLogger(libfreenect2::createConsoleLogger(libfreenect2::Logger::Level::None));
	libfreenect2::Freenect2 freenect2;
	libfreenect2::Freenect2Device *kinect = 0;

	cout << navirice::ansi::green("---CONFIGURING---") << endl;

	cout << "  Finding devices: " << std::flush;
	if(freenect2.enumerateDevices() == 0){
		cout << navirice::ansi::red("FAILURE") << endl;
		cout << "0 connected devices" << endl;
		return 1;
	}
	cout << navirice::ansi::green("SUCCESS") << " found: " << freenect2.enumerateDevices() << " device(s)" << endl;


	cout << "  Opening device 0: " << std::flush;
	string serial = freenect2.getDeviceSerialNumber(0);
	kinect = freenect2.openDevice(serial);
	if(kinect == 0){
		cout << navirice::ansi::red("FAILURE") << endl;
		cout << "Cannot open device 0" << endl;
		return 1;
	}
	cout << navirice::ansi::green("SUCCESS") << " serial: " << serial << endl;

	libfreenect2::FrameMap frames;
	int types = 0;
	types |= libfreenect2::Frame::Color;
	types |= libfreenect2::Frame::Ir | libfreenect2::Frame::Depth;
	libfreenect2::SyncMultiFrameListener listener(types);
	
	kinect->setColorFrameListener(&listener);
  kinect->setIrAndDepthFrameListener(&listener);	
	kinect->startStreams(true, true);

	server = new navirice::ImageDistributionServer(PORT);

	signal(SIGINT, finish_program);

	while(keep_alive) {
		auto start = std::chrono::steady_clock::now();
		// ACQUIRE COLOR FRAME FROM KINECT
		if(!listener.waitForNewFrame(frames, 10*1000)){
			cout << navirice::ansi::red("FAILED TO ACQUIRE FRAME\n");
		} else {
			
			libfreenect2::Frame *rgb_frame = frames[libfreenect2::Frame::Color];
			navirice::Image* rgb_image = new navirice::ImageImpl(
					rgb_frame->width,
					rgb_frame->height,
					rgb_frame->bytes_per_pixel,
					navirice::ImageDataType::UBYTE,
					rgb_frame->data,
					rgb_frame->bytes_per_pixel * rgb_frame->width * rgb_frame->height
					);

			libfreenect2::Frame *depth_frame = frames[libfreenect2::Frame::Depth];
			navirice::Image* depth_image = new navirice::ImageImpl(
					depth_frame->width,
					depth_frame->height,
					depth_frame->bytes_per_pixel,
					navirice::ImageDataType::FLOAT,
					depth_frame->data,
					depth_frame->bytes_per_pixel * depth_frame->width * depth_frame->height
					);
		
			libfreenect2::Frame *ir_frame = frames[libfreenect2::Frame::Ir];
			navirice::Image* ir_image = new navirice::ImageImpl(
					ir_frame->width,
					ir_frame->height,
					ir_frame->bytes_per_pixel,
					navirice::ImageDataType::UBYTE,
					ir_frame->data,
					ir_frame->bytes_per_pixel * ir_frame->width * ir_frame->height
					);	
	
			server->set_new_images(rgb_image, ir_image, depth_image);
	
			delete rgb_image;
			delete ir_image;
			delete depth_image;

			listener.release(frames);
		}
		auto duration = std::chrono::steady_clock::now() - start;
		cout << "------- push duration: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()) + " milliseconds\n";
	}

	// CLEANUP
	delete server;

	cout << "SHUTTING DOWN KINECT!" << endl;
	kinect->stop();
	kinect->close();
	cout << navirice::ansi::green("DONE") << endl;

	return 0;
}




