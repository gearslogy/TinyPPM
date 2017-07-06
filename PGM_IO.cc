#include "PGM_IO.h"
#include <stdio.h>
#include <cstdlib>
#include <varargs.h>
#include <cstring>




namespace TopVertex
{
	void *readImage(const char *path,ReadParams &params,ImageDataType readAsType)
	{
		FILE *fp;
		fp = fopen(path,"rb");

		// ============Read header Start================
		char header[3];
		fscanf(fp, "%s", header); // if get end/white ,will end reading ->P6
		//printf("%s\n" ,header);

		char width[15];
		fscanf(fp, "%s", width); 
		int iWidth = atoi(width);
		//printf("width:%d\n" ,iWidth);

		char height[15];
		fscanf(fp, "%s", height); 
		int iHeight = atoi(height);
		//printf("height:%d\n" ,iHeight);


		char maxPixelsValue[4];
		fscanf(fp, "%s", maxPixelsValue); // read the RGB maxpixels 255,but now streampos in \n
		int iMaxPixelsValue = atoi(maxPixelsValue);
		//printf("MaxPixelsValue:%d\n" ,iMaxPixelsValue);
		// ============Read Header End================


		params.width         = iWidth;
		params.height        = iHeight;
		params.maxPixelValue = iMaxPixelsValue;

	
		void *data = 0;
		if (readAsType==RGB_TYPE){
			data = malloc(sizeof(RGB) * iWidth * iHeight );
		}
		else{
			data = malloc(sizeof(uchar) * iWidth * iHeight * 3 );
		}

		if (!strcmp(header,"P3"))
		{ 
			params.ioType = ASCII_P3_TYPE;
			// P3 Type,ASCII
			for(int i=0;i<iWidth*iHeight;i++)
			{
				char CR[4];
				char CG[4];
				char CB[4];
				uchar UR,UG,UB;
				fscanf(fp,"%s",CR);
				fscanf(fp,"%s",CG);
				fscanf(fp,"%s",CB);
				UR = atoi(CR);
				UG = atoi(CG);
				UB = atoi(CB);
				if(readAsType == RGB_TYPE){
					RGB *rgb_data = (RGB*)data;
					rgb_data[i].R = UR;
					rgb_data[i].G = UG;
					rgb_data[i].B = UB;
				
				}
				if(readAsType == RAW_TYPE){
					uchar *raw_data = (uchar*)data;
					raw_data[i*3]      = UR;
					raw_data[i*3 + 1]  = UG;
					raw_data[i*3 + 2]  = UB;
				}
			}
			return data;

		}
		else if(!strcmp(header,"P6"))
		{
			params.ioType = BINARY_P6_TYPE;
			// P6 Type,Binary
			// jump \n , forward 1 bytes
			fseek(fp,1L,SEEK_CUR);
			for(int i=0;i<iWidth*iHeight;i++) 
			{
				uchar nextByte[3];
				fread(&nextByte,sizeof(uchar),3,fp);
				if(readAsType == RGB_TYPE){
					RGB *rgb_data = (RGB*)data;
					rgb_data[i].R = nextByte[0];
					rgb_data[i].G = nextByte[1];
					rgb_data[i].B = nextByte[2];
				}
				if(readAsType == RAW_TYPE){
					uchar *raw_data = (uchar*)data;
					raw_data[i*3]      = nextByte[0];
					raw_data[i*3 + 1]  = nextByte[1];
					raw_data[i*3 + 2]  = nextByte[2];
				}
			}
			return data;
		}
		else
		{
			fprintf(stderr,"Unkown header %s \n",header);
		}

		// default return 0
		return 0;
	}




	void writeImage(const void *data,const char *path,WriteParams param)
	{

		FILE *fp;
		fp = fopen(path,"w+");

		// ===========write header==================
		if(param.ioType == ASCII_P3_TYPE)
		{
			fprintf(fp,"%s\n","P3");
		}
		else if(param.ioType == BINARY_P6_TYPE)
		{
			fprintf(fp,"%s\n","P6");
		}
		else
		{
			fprintf(stderr,"Current API not support write %d line: %d type\n",param.ioType,__LINE__);
			fclose(fp);
			return;	
		}
		fprintf(fp,"%d %d\n",param.width,param.height);
		fprintf(fp,"%d\n",param.maxPixelValue);
		// ===========write header==================

		if (param.ioType == ASCII_P3_TYPE)
		{
			int wnum = param.width * param.height;
			if(param.imageType == RGB_TYPE)
			{
				RGB *pixelData = (RGB*)data;
				int i=0;
				while(i < wnum){
					fprintf(fp,"%d %d %d\n", pixelData[i].R,pixelData[i].G,pixelData[i].B );
					i++;
				}

			}
			else
			{
				uchar *pixelData = (uchar*)data;
				int i=0;
				while(i < wnum){
					fprintf(fp,"%d %d %d\n", pixelData[i*3],pixelData[i*3+1],pixelData[i*3+2] );
					i++;
				}
			}
		}
		else if(param.ioType == BINARY_P6_TYPE)
		{
			fseek(fp,-1L,SEEK_CUR);
			// Binary write out;
			if(param.imageType == RGB_TYPE)
			{
				// out RGB type
				RGB *pixelData = (RGB*)data;
				for(int i=0;i<param.width*param.height;i++)
				{
					uchar rgbData[3];
					rgbData[0] = pixelData[i].R;
					rgbData[1] = pixelData[i].G;
					rgbData[2] = pixelData[i].B;
					fwrite(&rgbData[0],sizeof(uchar),1,fp);
					fwrite(&rgbData[1],sizeof(uchar),1,fp);
					fwrite(&rgbData[2],sizeof(uchar),1,fp);
				}
			}
			else
			{
				// Raw uchar out
				uchar *pixelData = (uchar*)data;
				for(int i=0;i<param.width*param.height;i++)
				{
					uchar rawData[3];
					rawData[0] = pixelData[i*3];
					rawData[1] = pixelData[i*3 + 1];
					rawData[2] = pixelData[i*3 + 2];
					fwrite(rawData,sizeof(uchar),3,fp);
				}
			}
		}
		else
		{
			fprintf(stderr,"Current API not support write %d line: %d type\n",param.ioType,__LINE__);
			fclose(fp);
			return;
		}

		fclose(fp);

	}

	// Memory create and destroy

	RGB *allocateRGBArray(int width , int height)
	{
		RGB* data =  (RGB*)malloc(width*height * sizeof(RGB));
		return data;
	}
	RGB* allocateRGBArrayData(int npixels,...)
	{
		RGB* data =  (RGB*)malloc(npixels* sizeof(RGB));
		uchar *temp = (uchar*)malloc(npixels*3 *sizeof(uchar));
		va_list args;
		va_start(args, npixels*3 + 1);
		for (int i = 0; i <npixels*3+1; ++i){
			uchar arg = va_arg(args, uchar);
			if (i!=0){
				*(temp+i-1) = arg; // copy it to temp;
			}
		}
		va_end(args);
		for(int i=0;i<npixels;i++){
			data[i].R = temp[i*3];
			data[i].G = temp[i*3 + 1];
			data[i].B = temp[i*3 + 2];
		}
		free(temp);
		return data;
	}

	void destroyRGBArray(RGB *data)
	{
		free(data);
		data = NULL;
	}
	uchar *allocateRawArray(int width,int height)
	{
		uchar *data = (uchar*)malloc(width*height*3 *sizeof(uchar)); 
		return data;
	}
	uchar *allocateRawArrayData(int npixels,...)
	{
		/*
		allocateRawArrayData(2,2,   255,0,0,  255,0,0,   255,0,0,   0,0,255 )
		*/
		uchar *data = (uchar*)malloc(npixels*3 *sizeof(uchar)); 
		va_list args;
		va_start(args, npixels*3+1);
		for (int i = 0; i < npixels*3+1; ++i){
			uchar arg = va_arg(args, uchar);
			if(i!=0){
				*(data+i-1) = arg;
			}
		}
		va_end(args);
		return data;
	}
	void destroyRawArray(uchar *data)
	{
		free(data);
		data = NULL;
	}

	uchar *RgbToRaw(int npixels,const RGB *data)
	{
		uchar *udata = (uchar*)malloc(npixels*3 *sizeof(uchar)); 
		for(int i=0;i<npixels;i++)
		{
			udata[i*3]       = data[i].R;
			udata[i*3 + 1]   = data[i].G;
			udata[i*3 + 2]   = data[i].B;
		}
		return udata;
	}
	RGB *RawToRgb(int npixels,const uchar *data)
	{
		RGB *udata = (RGB*)malloc(npixels*sizeof(uchar)); 

		for(int i=0;i<npixels;i++)
		{
			udata[i].R = data[i*3];
			udata[i].G = data[i*3 + 1];
			udata[i].B = data[i*3 + 2];
		}
		return udata;
	}
}//end TopVertex namespace