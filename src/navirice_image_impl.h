#ifndef NAVIRICE_IMAGE_IMPL_H
#define NAVIRICE_IMAGE_IMPL_H

#include "navirice_config.h"
#include "navirice_image.h"

namespace navirice {

	class ImageImpl : public Image {
		private:
			std::string name_;
			unsigned width_, height_, channels_;
			ImageDataType type;
			ubyte* data;
			size_t data_size;
		public:
			ImageImpl(unsigned width_, unsigned height_, unsigned channels_, ImageDataType type, ubyte* data, size_t data_size);
			virtual ~ImageImpl();

			virtual unsigned width();
			virtual unsigned height();
			virtual unsigned channels();
			virtual ImageDataType data_type();
			virtual ubyte* get_raw_data();
			virtual size_t get_raw_data_size();
	};

}

#endif 
