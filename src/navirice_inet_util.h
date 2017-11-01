#ifndef NAVIRICE_INET_UTIL_H
#define NAVIRICE_INET_UTIL_H

#include <string>

namespace navirice {

	std::string int_to_ip(int ip)
	{
		unsigned char bytes[4];
		bytes[0] = ip & 0xFF;
		bytes[1] = (ip >> 8) & 0xFF;
		bytes[2] = (ip >> 16) & 0xFF;
		bytes[3] = (ip >> 24) & 0xFF;   
		return std::to_string(bytes[0]) + "." + std::to_string(bytes[1]) + "." + std::to_string(bytes[2]) + "." + std::to_string(bytes[3]); 	}

}

#endif
