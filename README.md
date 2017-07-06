# TinyPPM
a tiny ppm,pgm IO

# Simple Use:
write ths ascii P3 type ppm/pgm
    (1) custom value use RGB data
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
    
    (2) or use allocate
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
	
	(3) Raw uchar write
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
	
	(4) Binary write
	...
	WriteParams parms;
	...
	parms.ioType = BINARY_P6_TYPE;
	writeImage(data,"c:/test.ppm",parms);
	destroyRGBArray(data);
	
Read Image back:

    (1) read as raw
    ReadParams readParm;
	uchar *readBData = (uchar *) readImage("c:/testb.ppm",readParm,RAW_TYPE);

	printf("read c:/testb.ppm /width/height/maxpixelvalue /%d/%d/%d \n",
		readParm.width,readParm.height,readParm.maxPixelValue);
	destroyRawArray(readBData);
		
    (2) read as RGB
    ReadParams readParm;
	RGB *readBData = (RGB *) readImage("c:/testb.ppm",readParm,RGB_TYPE);
	printf("read c:/testb.ppm /width/height/maxpixelvalue /%d/%d/%d \n",
		readParm.width,readParm.height,readParm.maxPixelValue)
	destroyRGBArray(readBData)
	
	

	
	
	
