#ifndef NAVIRICE_IMAGE_DISTRIBUTION_SERVER_H
#define NAVIRICE_IMAGE_DISTRIBUTION_SERVER_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <mutex>
#include <thread>

#include "navirice_config.h"
#include "navirice_image.h"

#include "protobuf/navirice_image.pb.h"

namespace navirice {

	class ImageDistributionServer {
		private:
			// SERVER ATTRIB
			uint16_t port;
			int listener;
			struct sockaddr_in serv_addr;

			// SERVER DATA
			std::mutex current_image_mutex;
			ProtoImageSet images;
			uint64_t image_count;

			// THREADS
			std::thread* scl;
			void server_connection_listener();
			
			// UTIL
			std::string get_prompt();
			void handle_request(int cli_sock, sockaddr_in cli_addr);
			void send_images(int cli_sock, sockaddr_in cli_addr);

		public:
			ImageDistributionServer(uint16_t port);
			~ImageDistributionServer();
			void set_new_images(Image* new_color_image, Image* new_ir_image, Image* new_depth_image);
	};

}

#endif
