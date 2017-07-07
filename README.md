# TinyPPM
a tiny ppm,pgm IO


Memory:
    one RGB have three uchar


    
# Simple Use:
write ppm/pgm image

    PPMIO imio;
	PPMIO::ReadParam readParam;
	void *data = imio.readImage("c:/test.ppm",readParam, PPMIO::RGB_TYPE);
	/* 
	// Get incoming picture basic info.
	readParam.width
	readParam.height
	readParam.maxPixelValue
	*/

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
	
	
	
