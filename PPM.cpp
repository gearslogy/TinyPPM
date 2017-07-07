#include "PPM.h"

PPMIO::PPMIO()
{

}
PPMIO::~PPMIO()
{

}

void *PPMIO::readImage(const char *path ,ReadParam &param,ImageDataType readAsType)
{
	ifstream streamIn;
	streamIn.open(path,ios::binary);
	char header[3];
	streamIn >> header>> param.width >> param.height >> param.maxPixelValue;
	streamIn.ignore(256, '\n');

	RGB *rgbData = new RGB[param.width*param.height];
	streamIn.read(reinterpret_cast<char*>(rgbData), param.width * param.height * sizeof(rgbData));


	if(!strcmp(header,"P6")){
		param.imageIOType = BINARY_P6_TYPE;
	}
	else if(!strcmp(header,"P3"))
	{
		param.imageIOType = ASCII_P3_TYPE;
	}
	else
	{
		cout << "unkown type\n";
	}

	if(readAsType==RGB_TYPE)
	{
		streamIn.close();
		return rgbData;
	}
	else
	{

		unsigned char *udata = RgbToRaw(param.width*param.height,rgbData);
		delete []rgbData;
		streamIn.close();
		return udata;
	}
	streamIn.close();
	return 0;
}
void PPMIO::writeImage(const char *path ,const void *data,WriteParam param )
{
	int w = param.width;
	int h = param.height;
	int m = param.maxPixelValue;
	using namespace std;

	ofstream streamOut;
	streamOut.open(path,ios::binary);

	if(param.imageIOType == BINARY_P6_TYPE)
	{
		streamOut << "P6"<< "\n"
			<< w << " "
			<< h << "\n"
			<< m << "\n";
	}
	else
	{
		streamOut << "P3"<< "\n"
			<< w << " "
			<< h << "\n"
			<< m << "\n";
	}


	if (param.imageIOType == BINARY_P6_TYPE)
	{

		if(param.imageType == RGB_TYPE)
		{
			RGB *rgbData = (RGB*)data;
			streamOut.write((char*)rgbData, sizeof(RGB)*w*h);
			streamOut.close();
		}

		else
		{
			unsigned char *rgbData = (unsigned char*)data;
			streamOut.write((char*)rgbData, sizeof(unsigned char)*w*h*3);
			streamOut.close();
		}


	}
	else if(param.imageIOType == ASCII_P3_TYPE)
	{
		if(param.imageType == RGB_TYPE)
		{
			RGB *rgbData = (RGB*)data;
			for(int i=0;i<param.width*param.height;i++)
			{
				char rstr[10];
				char gstr[10];
				char bstr[10];
				sprintf(rstr,"%d",rgbData[i].R);
				sprintf(gstr,"%d",rgbData[i].G);
				sprintf(bstr,"%d",rgbData[i].B);
				streamOut << rstr << " " << gstr << " " << bstr<<"\n";
			}
			streamOut.close();
		}

		else
		{
			unsigned char *rgbData = (unsigned char*)data;
			for(int i=0;i<param.width*param.height;i++)
			{
				char rstr[10];
				char gstr[10];
				char bstr[10];
				sprintf(rstr,"%d",rgbData[i*3]);
				sprintf(gstr,"%d",rgbData[i*3+1]);
				sprintf(bstr,"%d",rgbData[i*3+2]);
				streamOut << rstr << " " << gstr << " " << bstr<<"\n";
			}
			streamOut.close();
		}

	}
	else
	{
		streamOut.close();
		cout << "can not write with IO type " << param.imageIOType <<std::endl;
		return ;

	}

}