#include "GPU_ProcessImage.h"
#include <stdio.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#define THREADS_PER_BLOCK 1024

#define CHECK_CUDA_STATUS(STATUS)\
{\
    if (STATUS != cudaSuccess)\
    {\
        fprintf(stdout,"Error in line %d\n ",__LINE__);\
    }\
}\

__global__ void gpuGreyImage(PPMIO::RGB *dev_srcImage , PPMIO::RGB *dev_desImage,int npixels)
{
	const long index = threadIdx.x + blockDim.x*blockIdx.x;
	if(index < npixels*3)
	{
		unsigned char r = unsigned char(float(dev_srcImage[index].R) * 0.244f);
		unsigned char g = unsigned char(float(dev_srcImage[index].G) * 0.587f);
		unsigned char b = unsigned char(float(dev_srcImage[index].B) * 0.114f);
		unsigned char i = r + g +b;
		dev_desImage[index].R = i;
		dev_desImage[index].G = i;
		dev_desImage[index].B = i;
	}
}

void processImage(PPMIO::RGB *host_srcImage, 
		PPMIO::RGB *host_desImage,int npixels)
{
	printf("Test in gpu compile\n");
	cudaError_t cstat;
	cstat = cudaSetDevice(0);
	CHECK_CUDA_STATUS(cstat);

	PPMIO::RGB *dev_src;
	PPMIO::RGB *dev_des;
	cstat = cudaMallocManaged(&dev_src,sizeof(PPMIO::RGB) * npixels);
	CHECK_CUDA_STATUS(cstat);
	cstat = cudaMallocManaged(&dev_des,sizeof(PPMIO::RGB) * npixels);
	CHECK_CUDA_STATUS(cstat);

	cstat = cudaMemcpy(dev_src,host_srcImage,sizeof(PPMIO::RGB)*npixels,cudaMemcpyHostToDevice);



	int NBLOCKS = npixels/THREADS_PER_BLOCK;
	if(NBLOCKS<=0)
	{
		NBLOCKS = 1;
	}
	gpuGreyImage<<<NBLOCKS,THREADS_PER_BLOCK>>>(dev_src,dev_des,npixels);

	cstat = cudaMemcpy(host_desImage,dev_des,sizeof(PPMIO::RGB)*npixels,cudaMemcpyDeviceToHost);
	CHECK_CUDA_STATUS(cstat);
	
	cudaFree(dev_src);
	cudaFree(dev_des);


}