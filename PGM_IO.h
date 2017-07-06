

/*
2017.7.5
Tiny PGM IO
liuyangping207@qq.com
*/
#ifndef PGM_IO_H_
#define PGM_IO_H_

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

namespace TopVertex
{
	#ifdef __cplusplus
	extern "C" {
	#endif

	typedef struct RGB
	{
		uchar R;
		uchar G;
		uchar B;
	}RGB;


	enum ImageDataType{RGB_TYPE=0x00,RAW_TYPE=0x01};
	enum ImageFileIOType{ASCII_P3_TYPE=0x00,BINARY_P6_TYPE=0x01};

	typedef struct WriteParams
	{

		ImageDataType imageType;
		ImageFileIOType ioType;
		uint width;
		uint height;
		uint maxPixelValue;

	}WriteParams;

	typedef struct ReadParams
	{
		ImageFileIOType ioType;  // Data will read as (binary?ASCII)type
		uint width;         // Image read in width
		uint height;        // Image read height
		uint maxPixelValue; // Image read max pixel value

	}ReadParams;


	// write data from const void *data
	void writeImage(const void *data,const char *path,WriteParams param);

	// read image return raw/rgb data
	void *readImage(const char *path,ReadParams &params,ImageDataType readAsType=RGB_TYPE);

	// memory RGB or Raw
	RGB* allocateRGBArray(int width , int height);
	RGB* allocateRGBArrayData(int npixels,...);
	void destroyRGBArray(RGB *data);

	uchar *allocateRawArray(int width,int height);
	uchar *allocateRawArrayData(int npixels,...);
	void destroyRawArray(uchar *data);


	// data convert
	uchar *RgbToRaw(int npixels,const RGB *data);
	RGB *RawToRgb(int npixels,const uchar *data);



	#ifdef __cplusplus
	}
	#endif

} // end of namespace




#endif