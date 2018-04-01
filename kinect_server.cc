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

int program_exit_counter = 0;

void finish_program(int input){
	keep_alive = false;
	program_exit_counter++;
	if(program_exit_counter >=3){
		std::cout << "*****************************\nOVERRIDING FOR FORCED EXIT!" << std::endl;
		exit(3);
	}
}

class IOCW;


int gridwidth = 32;
int gridheight = 32;
float cutoff = 0.5;
//todo test intties
float * ref_background = 0;
int refwidth = 0;
int refheight = 0;
navirice::ubyte * griddata = 0;
navirice::Image* bgref = 0;


void setRefBG(libfreenect2::Frame * ref){
	refwidth = ref->width;
	refheight = ref->height;
	if(ref_background) free(ref_background);
	ref_background = (float*)malloc(refwidth * refheight * sizeof(float));
	int x, y;
	for(y = 0; y < refheight; y++){
		float * inpline = &((float*)ref->data)[y*refwidth];
		float * outline = &ref_background[y*refwidth];
		for(x = 0; x < refwidth; x++){
			//lolslow
			inpline[x] = outline[x] - 50.0;
		}
	}
}

void calculateBG(libfreenect2::Frame * cur){
	//todo optimizzle the fuck outta this
	//todo SIMD SLAMMER!
	int maxblack = (1.0-cutoff) * gridwidth * gridheight;
	int maxwhite = (cutoff) * gridwidth * gridheight;
	int x, y;
	int sy = 0;
	int slammajammay = refheight * gridheight;
	int slammajammax = refwidth * gridwidth;
	for(y =0; y < gridheight; y++){
		int ey = slammajammay /y;
		navirice::ubyte * outline = &griddata[y*gridwidth];
		int sx = 0;
		int dy = ey-sy;
		for(x = 0; x < gridwidth; x++){
			int ex = slammajammax /x;
			int numinsec = (ex-sx) * dy;
			int maxwhite = (cutoff) * (float)numinsec;
			int maxblack = numinsec-maxwhite;

			//todo be a retard here and unroll loop
			int cx, cy;
			int countwhite = 0;
			int countblack = 0;
			outline[x] = 0;
			for(cy = sy; cy < ey; cy++){
				float * curline = &((float*)cur->data)[cy * refwidth];
				float * refline = &ref_background[cy * refwidth];
				for(cx = sx; cx < ex; cx++){
//					if(curline[cx] < refline[cx]) countwhite++;
//					else countblack++;
					int result = outline[cx] < refline[cx];
					countwhite += result;
					countblack += !result;
				}
				if(countwhite>=maxwhite){ outline[x] =1; break;}
				if(countblack>= maxblack) break;
			}
		}
		sy = ey;
	}
}

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

	server = new navirice::ImageDistributionServer(PORT);
	auto settings = server->get_server_settings();
	auto r = kinect->startStreams(true, true);

	signal(SIGINT, finish_program);

	while(keep_alive) {

		auto new_settings = server->get_server_settings();
		if(!settings.is_equal(new_settings)){
			settings = new_settings;
			std::cout << "------------ SERVER SETTINGS CHANGED ----------------\n";
			std::cout << "IR: " << settings.IR << std::endl;
			std::cout << "RGB: " << settings.RGB << std::endl;
			std::cout << "Depth: " << settings.Depth << std::endl;
			std::cout << "BG: " << settings.BG << std::endl;
			std::cout << "-----------          END             ----------------\n";
//			kinect->stop();
			kinect->startStreams(settings.RGB, settings.IR || settings.Depth || settings.BG);

			//allocate BGgrid if not already done
			if(settings.BG){
				if(!griddata) griddata = (navirice::ubyte*)malloc(gridwidth * gridheight);
			}
		}

		auto start = std::chrono::steady_clock::now();
		// ACQUIRE COLOR FRAME FROM KINECT
		//std::cout << "WAITING FOR NEW FRAME" << std::endl;
		if(!listener.waitForNewFrame(frames, 100)){
			cout << navirice::ansi::red("FAILED TO ACQUIRE FRAME\n");
		} else {
			//std::cout << "ACQUIRED NEW FRAME" << std::endl;

			libfreenect2::Frame *rgb_frame = NULL;
			libfreenect2::Frame *depth_frame = NULL;
			libfreenect2::Frame *ir_frame = NULL;
			navirice::Image* rgb_image = NULL;
			navirice::Image* depth_image = NULL;
			navirice::Image* ir_image = NULL;
			navirice::Image* bg_image = NULL;

			if(settings.RGB){
				rgb_frame = frames[libfreenect2::Frame::Color];
				if(rgb_frame) rgb_image = new navirice::ImageImpl(
						rgb_frame->width,
						rgb_frame->height,
						rgb_frame->bytes_per_pixel,
						navirice::ImageDataType::UBYTE,
						rgb_frame->data,
						rgb_frame->bytes_per_pixel * rgb_frame->width * rgb_frame->height
						);
			}

			//std::cout << "RGB SET" << std::endl;

			if(settings.IR || settings.Depth || settings.BG){
				depth_frame = frames[libfreenect2::Frame::Depth];
				ir_frame = frames[libfreenect2::Frame::Ir];
			}

			if(settings.Depth){
				if(depth_frame) depth_image = new navirice::ImageImpl(
						depth_frame->width,
						depth_frame->height,
						depth_frame->bytes_per_pixel,
						navirice::ImageDataType::FLOAT,
						depth_frame->data,
						depth_frame->bytes_per_pixel * depth_frame->width * depth_frame->height
						);
			}
			if(settings.IR){
				if(ir_frame) ir_image = new navirice::ImageImpl(
						ir_frame->width,
						ir_frame->height,
						ir_frame->bytes_per_pixel,
						navirice::ImageDataType::FLOAT,
						ir_frame->data,
						ir_frame->bytes_per_pixel * ir_frame->width * ir_frame->height
						);
			}
			//todo
			if(settings.BG && depth_frame){
				if(!ref_background){
					setRefBG(depth_frame);
				} else {
					//time to generate the data!
					calculateBG(depth_frame);
					bg_image = new navirice::ImageImpl(
						32,
						32,
						1,
						navirice::ImageDataType::UBYTE,
						griddata,
						gridwidth * gridheight
					);
				}
			}

			//std::cout << "IR DEPTH SET" << std::endl;

			//todo set new BG image
			server->set_new_images(rgb_image, ir_image, depth_image, bg_image);

			//std::cout << "NEW IMAGES SET" << std::endl;

			if(rgb_image) delete rgb_image;
			if(ir_image) delete ir_image;
			if(depth_image) delete depth_image;
			if(bg_image) delete bg_image;

			listener.release(frames);
		}
		auto duration = std::chrono::steady_clock::now() - start;
		cout << "------- push duration: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()) + " milliseconds\n";
	}

	// CLEANUP
	delete server;
	if(griddata) free(griddata);

	cout << "SHUTTING DOWN KINECT!" << endl;
	kinect->stop();
	kinect->close();
	cout << navirice::ansi::green("DONE") << endl;

	return 0;
}




