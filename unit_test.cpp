#include <stdio.h>
#include <cstdlib>
#include "PPM.h"
#include <fstream>
#include "GPU_ProcessImage.h"

void readWriteAsciiCPP()
{

	PPMIO imio;
	PPMIO::ReadParam readParam;
	void *data = imio.readImage("c:/test.ppm",readParam, PPMIO::RGB_TYPE);

	PPMIO::WriteParam writeParam;
	writeParam.width = readParam.width;
	writeParam.height = readParam.height;
	writeParam.imageIOType = PPMIO::BINARY_P6_TYPE;
	writeParam.maxPixelValue = 255;
	writeParam.imageType = PPMIO::RGB_TYPE;
	imio.writeImage("c:/copy_ascii.ppm",data,writeParam);
	
	
	
	/*
	// write binary
	PPMIO::WriteParam writeParam;
	writeParam.width = readParam.width;
	writeParam.height = readParam.height;
	writeParam.imageIOType = PPMIO::ASCII_P3_TYPE;
	writeParam.maxPixelValue = 255;
	writeParam.imageType = PPMIO::RGB_TYPE;
	imio.writeImage("c:/copy_ascii.ppm",data,writeParam);
	*/

}


void GPUReadWriteAsciiCPP()
{

	PPMIO imio;
	PPMIO::ReadParam readParam;
	void *data = imio.readImage("c:/clb_cpu.pbm",readParam, PPMIO::RGB_TYPE);

	int npixels = readParam.width * readParam.height;

	PPMIO::RGB* gpuToHostData = new PPMIO::RGB[npixels];
	processImage((PPMIO::RGB*)data,gpuToHostData,npixels);
	cout << "GPU compute end\n";


	PPMIO::WriteParam writeParam;
	writeParam.width = readParam.width;
	writeParam.height = readParam.height;
	writeParam.imageIOType = PPMIO::BINARY_P6_TYPE;
	writeParam.maxPixelValue = 255;
	writeParam.imageType = PPMIO::RGB_TYPE;
	imio.writeImage("c:/clb_gpu.pbm",gpuToHostData,writeParam);


	// delete source image data
	delete []data;
	// delete gpu to host image;
	delete []gpuToHostData;
}


int main(int argc,char **argv)
{
	//writeCPP();
	//readWriteAsciiCPP();
	GPUReadWriteAsciiCPP();
	cin.get();

	
	exit(EXIT_SUCCESS);
}



