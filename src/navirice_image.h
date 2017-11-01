#ifndef NAVIRICE_IMAGE_H
#define NAVIRICE_IMAGE_H

#include <cstdlib>
#include <string>

namespace navirice {

	typedef unsigned char ubyte;

	enum ImageDataType {
		FLOAT = 1,
		UBYTE = 2
	};

	class Image {
		public:
			virtual ~Image(){};
			virtual unsigned width() = 0;
			virtual unsigned height() = 0;
			virtual unsigned channels() = 0;
			virtual ImageDataType data_type() = 0;
			virtual ubyte* get_raw_data() = 0;
			virtual size_t get_raw_data_size() = 0;
	};

	/* If you are using DI (DI for depth image)
	 *
	 * Max for DI single pixel is 4500.0, min is 0
	 * Image is formatted in a weird way, its upside down. Thanks Kinect...
	 * 
	 * Convention is:
	 * raw_data[width * y + x]
	 *
	 * To get a single pixel with x and y instead use:
	 * raw_data[width * (height-y) + x] 
	 *
	 *
	 */
}	

#endif 
