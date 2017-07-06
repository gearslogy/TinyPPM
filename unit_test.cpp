#include <stdio.h>
#include <cstdlib>
#include "PGM_IO.h"

using namespace TopVertex;


void testWriteAllocateRGB()
{
	int width = 2;
	int height = 2;
	uint imagePixels = width * height;
	RGB *data = allocateRGBArray(width,height);
	for (int i=0;i<imagePixels;i++)
	{
		data[i].R = 255/(i+1);
		data[i].G = 255/(i+1);
		data[i].B = 255/(i+1);
	}

	WriteParams parms;
	parms.width = width;
	parms.height = height;
	parms.maxPixelValue = 255;
	parms.imageType = ImageDataType::RGB_TYPE;
	parms.ioType = ASCII_P3_TYPE;
	writeImage(data,"c:/test.ppm",parms);
	destroyRGBArray(data);
	
}

void testWriteAllocateRGBData()
{
	int width = 2;
	int height = 2;
	uint imagePixels = width * height;
	RGB *data = allocateRGBArrayData(imagePixels,110,0,0, 0,255,0, 0,0,255, 0,0,0);

	WriteParams parms;
	parms.width = width;
	parms.height = height;
	parms.maxPixelValue = 255;
	parms.imageType = ImageDataType::RGB_TYPE;
	parms.ioType = ASCII_P3_TYPE;
	writeImage(data,"c:/test.ppm",parms);
	destroyRGBArray(data);
}

void testWriteAllocateRaw()
{
	int width = 2;
	int height = 2;
	uint imagePixels = width * height;
	uchar *data = allocateRawArray(width,height);
	for (int i=0;i<imagePixels;i++)
	{
		data[i*3]     = 255/(i+1);
		data[i*3 + 1] = 255/(i+1);
		data[i*3 + 2] = 255/(i+1);
	}


	WriteParams parms;
	parms.width = width;
	parms.height = height;
	parms.maxPixelValue = 255;
	parms.imageType = ImageDataType::RAW_TYPE;
	parms.ioType = ASCII_P3_TYPE;
	writeImage(data,"c:/test.ppm",parms);

	destroyRawArray(data);
}

void testWriteAllocateRawData()
{
	// create 2 2 pixels
	int width = 2;
	int height = 2;
	uint imagePixels = width * height;
	uchar *data = allocateRawArrayData(imagePixels,110,0,0, 0,255,0, 0,0,255, 0,0,0);

	WriteParams parms;
	parms.width = width;
	parms.height = height;
	parms.maxPixelValue = 255;
	parms.imageType = ImageDataType::RAW_TYPE;
	parms.ioType = ASCII_P3_TYPE;
	writeImage(data,"c:/test.ppm",parms);
	destroyRawArray(data);
}


void ReadTest()
{
	ReadParams params;
	readImage("c:/test.ppm",params,RGB_TYPE);
}


void ReadBinaryAndWriteBinaryRGB()
{
	ReadParams readParm;
	RGB *readBData = (RGB*) readImage("c:/testb.ppm",readParm,RGB_TYPE);
	printf("read c:/testb.ppm /width/height/maxpixelvalue /%d/%d/%d \n",
		readParm.width,readParm.height,readParm.maxPixelValue);


	WriteParams writeParm;
	writeParm.width = readParm.width;
	writeParm.height = readParm.height;
	writeParm.maxPixelValue = readParm.maxPixelValue;
	writeParm.ioType = BINARY_P6_TYPE;
	writeParm.imageType = RGB_TYPE;

	writeImage(readBData,"c:/testbRD.ppm",writeParm);
	destroyRGBArray(readBData);


	
	printf("\n============readback c:/testbRD.ppm=================== \n");
	ReadParams readCheckParam;
	RGB *readBRDData = (RGB*) readImage("c:/testbRD.ppm",readCheckParam,RGB_TYPE);
	printf("\nread testbRD back /width/height/maxpixelvalue /%d/%d/%d \n",
		readCheckParam.width,readCheckParam.height,readCheckParam.maxPixelValue);
	destroyRGBArray(readBRDData);

}
void ReadBinaryAndWriteBinaryRAW()
{
	ReadParams readParm;
	uchar *readBData = (uchar *) readImage("c:/testb.ppm",readParm,RAW_TYPE);
	printf("read c:/testb.ppm /width/height/maxpixelvalue /%d/%d/%d \n",
		readParm.width,readParm.height,readParm.maxPixelValue);

	WriteParams writeParm;
	writeParm.width = readParm.width;
	writeParm.height = readParm.height;
	writeParm.maxPixelValue = readParm.maxPixelValue;
	writeParm.ioType = BINARY_P6_TYPE;
	writeParm.imageType = RAW_TYPE;
	writeImage(readBData,"c:/testb_readAsRaw_writeAsBinary.ppm",writeParm);
	destroyRawArray(readBData);
}

void ReadBinaryAndWriteASCLLRGB()
{
	ReadParams readParm;
	RGB *readBData = (RGB *) readImage("c:/testb.ppm",readParm,RGB_TYPE);
	printf("read c:/testb.ppm /width/height/maxpixelvalue /%d/%d/%d \n",
		readParm.width,readParm.height,readParm.maxPixelValue);
	WriteParams writeParm;
	writeParm.width = readParm.width;
	writeParm.height = readParm.height;
	writeParm.maxPixelValue = readParm.maxPixelValue;
	writeParm.ioType = ASCII_P3_TYPE;
	writeParm.imageType = RGB_TYPE;
	writeImage(readBData,"c:/testb_readAsRGB_writeAsASCII.ppm",writeParm);
	destroyRGBArray(readBData);

}
void ReadBinaryAndWriteASCLLRAW()
{
	ReadParams readParm;
	uchar *readBData = (uchar *) readImage("c:/testb.ppm",readParm,RAW_TYPE);

	printf("read c:/testb.ppm /width/height/maxpixelvalue /%d/%d/%d \n",
		readParm.width,readParm.height,readParm.maxPixelValue);

	WriteParams writeParm;
	writeParm.width = readParm.width;
	writeParm.height = readParm.height;
	writeParm.maxPixelValue = readParm.maxPixelValue;
	writeParm.ioType = ASCII_P3_TYPE;
	writeParm.imageType = RAW_TYPE;
	writeImage(readBData,"c:/testb_readAsRaw_writeAsASCII.ppm",writeParm);
	destroyRawArray(readBData);

}

void ReadASCIIRawAsBinary()
{
	ReadParams readParm;
	uchar *readBData = (uchar *) readImage("c:/test.ppm",readParm,RAW_TYPE);

	printf("read c:/test.ppm /width/height/maxpixelvalue /%d/%d/%d \n",
		readParm.width,readParm.height,readParm.maxPixelValue);

	WriteParams writeParm;
	writeParm.width = readParm.width;
	writeParm.height = readParm.height;
	writeParm.maxPixelValue = readParm.maxPixelValue;
	writeParm.ioType = BINARY_P6_TYPE;
	writeParm.imageType = RAW_TYPE;
	writeImage(readBData,"c:/srcASCII_readAsRaw_writeAsBinary.ppm",writeParm);
	destroyRawArray(readBData);
}

void ReadASCIIRGBAsBinary()
{
	ReadParams readParm;
	RGB *readBData = (RGB *) readImage("c:/test.ppm",readParm,RGB_TYPE);

	printf("read c:/test.ppm /width/height/maxpixelvalue /%d/%d/%d \n",
		readParm.width,readParm.height,readParm.maxPixelValue);

	WriteParams writeParm;
	writeParm.width = readParm.width;
	writeParm.height = readParm.height;
	writeParm.maxPixelValue = readParm.maxPixelValue;
	writeParm.ioType = BINARY_P6_TYPE;
	writeParm.imageType = RGB_TYPE;
	writeImage(readBData,"c:/srcASCII_readAsRGB_writeAsBinary.ppm",writeParm);
	destroyRGBArray(readBData);

}
int main(int argc,char **argv)
{
	//testWriteAllocateRaw();
	//testWriteAllocateRGBData();
	//testWriteAllocateRawData();
	//readFromDisk();
	//speedReadFromDisk();
	//ReadTest();
	//ReadBinaryAndWriteBinaryRGB();
	//ReadBinaryAndWriteBinaryRAW();
	//ReadBinaryAndWriteASCLLRGB();
	//ReadBinaryAndWriteASCLLRAW();
	//ReadASCIIRawAsBinary();
	//ReadASCIIRGBAsBinary();
	getchar();
	exit(EXIT_SUCCESS);
}