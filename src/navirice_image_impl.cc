#include "navirice_image_impl.h"

#include <iostream>
#include <cstdint>
#include <cstring>

navirice::ImageImpl::ImageImpl(unsigned width_, unsigned height_, unsigned channels_, ImageDataType type, ubyte* data, size_t data_size){
	this->width_ = width_;
	this->height_ = height_;
	this->channels_ = channels_;
	this->type = type;
	this->data = data;
	this->data_size = data_size;
	this->data = (ubyte*)malloc(data_size);
	
	std::memcpy(this->data, data, data_size);
}

unsigned navirice::ImageImpl::width(){ return this->width_; }

unsigned navirice::ImageImpl::height(){ return this->height_; }

unsigned navirice::ImageImpl::channels(){ return this->channels_; }

navirice::ImageDataType navirice::ImageImpl::data_type(){ return this->type; }

navirice::ubyte* navirice::ImageImpl::get_raw_data(){ return this->data; }

size_t navirice::ImageImpl::get_raw_data_size(){ return this->data_size; }

navirice::ImageImpl::~ImageImpl(){
	if(this->data) free(this->data);
	this->data = NULL;
}
