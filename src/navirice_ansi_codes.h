#ifndef NAVIRICE_ANSI_CODES_H
#define NAVIRICE_ANSI_CODES_H

#include <iostream>

namespace navirice {
	namespace ansi {
		static std::string red(std::string str){
			return "\033[1;31m" + str + "\033[0m";
		}

		static std::string green(std::string str){
			return "\033[1;32m" + str + "\033[0m";
		}

		static std::string yellow(std::string str){
			return "\033[1;33m" + str + "\033[0m";
		}

		static std::string blue(std::string str){
			return "\033[1;34m" + str + "\033[0m";
		}

		static std::string erase_line(){
			return "\r\033[K";
		}
	}

}

#endif
