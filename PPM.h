#ifndef PPM_H_
#define PPM_H_


#include <iostream>
#include <memory>
#include <fstream>
using namespace std;
class PPMIO
{
public:
	enum ImageDataType{RGB_TYPE=0x00,RAW_TYPE=0x01};
	enum ImageFileIOType{ASCII_P3_TYPE=0x00,BINARY_P6_TYPE=0x01};

	struct WriteParam
	{
		int width;
		int height;
		int maxPixelValue;
		ImageDataType imageType;
		ImageFileIOType imageIOType;
	};

	struct ReadParam
	{
		int width;
		int height;
		int maxPixelValue;
		ImageFileIOType imageIOType;
	};


	struct RGB
	{
		unsigned char R;
		unsigned char G;
		unsigned char B;
	};


	inline unsigned char *RgbToRaw(int npixels,const RGB *data)
	{
		unsigned char *udata = new unsigned char[npixels *3];
		for(int i=0;i<npixels;i++)
		{
			udata[i*3]       = data[i].R;
			udata[i*3 + 1]   = data[i].G;
			udata[i*3 + 2]   = data[i].B;
		}
		return udata;
	}
	inline RGB *RawToRgb(int npixels,const unsigned char *data)
	{
		RGB *udata = new RGB[npixels];
		for(int i=0;i<npixels;i++)
		{
			udata[i].R = data[i*3];
			udata[i].G = data[i*3 + 1];
			udata[i].B = data[i*3 + 2];
		}
		return udata;
	}



public:
	PPMIO();
	~PPMIO();


	void* readImage(const char *path ,ReadParam &param,ImageDataType readAsType);
	void writeImage(const char *path ,const void *data,WriteParam param );

};




#endif