#include <iostream>
#include <signal.h>
#include "src/navirice.h"

navirice::ImageDistributionServer* server;
bool keep_alive = true;

void finish_program(int input){
	delete server;
	keep_alive = false;
}

int main(){
	std::cout << navirice::ansi::red("TEST PROGRAM IS ALIVE...") << std::endl;
	server = new navirice::ImageDistributionServer(29000);
	
	signal(SIGINT, finish_program);

	auto settings = navirice::ServerSettings();

	while(keep_alive) {
		server->set_new_images(NULL,NULL,NULL);
		if(!settings.is_equal(server->get_server_settings())){
			settings = server->get_server_settings();
			std::cout << "------------ SERVER SETTINGS CHANGED ----------------\n";
			std::cout << "IR: " << settings.IR << std::endl;
			std::cout << "RGB: " << settings.RGB << std::endl;
			std::cout << "Depth: " << settings.Depth << std::endl;
			std::cout << "-----------          END             ----------------\n";
		}
		usleep(1000000);
	}

	return 0;
}
