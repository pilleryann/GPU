#include "Indice2D.h"
#include "cudaTools.h"
#include <iostream>

static __global__ void add(float* ptrDevV1,float* ptrDevV2,int n,float* ptrDevResult);
static __device__ float work(float v1,float v2);
void useAdd();

static __global__ void add(float* ptrDevV1,float* ptrDevV2,int n,float* ptrDevResult){
    const int NBR_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();
    int s = TID;

    while(s<n){

	ptrDevResult[s] = work(ptrDevV1[s],ptrDevV2[s]);
	s+=NBR_THREAD;

    }
}

static  __device__ float work(float v1,float v2){
	return v1 + v2;

    }


__host__ void fillArray(float* floatArray,int n, int k){
    for(int i=0;i<n;i++){
	     floatArray[i]=(i+1)*k;
           }
}

void useAdd(){
     int n=7;
    dim3 dg = dim3(2,2,1);
    dim3 db = dim3(2,2,1);

    float v1[n];
    fillArray(v1,n,1);
    float v2[n];
    fillArray(v2,n,10);
    float vResult[n];
    float * ptrDevV1 = NULL;
    float * ptrDevV2 = NULL;
    float * ptrDevResult = NULL;
    size_t size = n*sizeof(float);
    HANDLE_ERROR(cudaMalloc(&ptrDevV1,size));
    HANDLE_ERROR(cudaMalloc(&ptrDevV2,size));
    HANDLE_ERROR(cudaMalloc(&ptrDevResult,size));

    HANDLE_ERROR(cudaMemset(ptrDevV1,0,size));
    HANDLE_ERROR(cudaMemset(ptrDevV2,0,size));
    HANDLE_ERROR(cudaMemset(ptrDevResult,0,size));
    //memCPy (dst,src,size,flag-copy)
    HANDLE_ERROR(cudaMemcpy(ptrDevV1,v1,size,cudaMemcpyHostToDevice));
    HANDLE_ERROR(cudaMemcpy(ptrDevV2,v2,size,cudaMemcpyHostToDevice));
    add<<<dg,db>>>(ptrDevV1,ptrDevV2,n,ptrDevResult);//asynchronous
    HANDLE_ERROR(cudaMemcpy(vResult,ptrDevResult,size,cudaMemcpyDeviceToHost));//barriere implicite de sync
    std::cout << vResult[0];
    for(int i=1;i<n;i++){
	 std::cout << " , " << vResult[i];
    }
    std::cout<< std::endl;
}



