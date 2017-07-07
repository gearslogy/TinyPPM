#pragma once
#include "PPM.h"
extern "C"
{
	void processImage(PPMIO::RGB *host_srcImage, 
		PPMIO::RGB *host_desImage,int npixels);
};