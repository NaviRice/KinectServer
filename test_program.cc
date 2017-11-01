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

	while(keep_alive) usleep(100000);

	return 0;
}
