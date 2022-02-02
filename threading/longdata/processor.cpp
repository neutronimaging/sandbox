#include <thread>
#include <chrono>
#include <iostream>
#include <list>
#include <cmath>

#include "processor.h"

Processor::Processor() :
    nData(0UL),
    data(nullptr),
    dest1(nullptr),
    dest2(nullptr)
{

}

Processor::~Processor()
{
    if (data)
        delete [] data;

    if (dest1)
        delete [] dest1;

    if (dest2)
        delete [] dest2;

}

int Processor::run(float *pSrc, float *pDst, float value)
{
    return process(pSrc, pSrc+nData, pDst, value);
}

int Processor::runp(float *pSrc, float *pDst, float value)
{
    auto nThreads = std::thread::hardware_concurrency();
    std::cout<<"runp "<<nThreads<<" threads\n";
    size_t blockSize=nData / nThreads;
    std::list<std::thread> tlist;
    size_t begin=0;
    size_t end=blockSize;
    cnt = 0;
    for (auto i=0; i<nThreads; ++i) {
        tlist.push_back(std::thread([=] { process(pSrc+begin, pSrc+end,pDst+begin,value); }));
        begin+=blockSize;
        end+=blockSize;
    }

    for (auto & it: tlist)
        it.join();

    return 0;
}

int Processor::runps(float *pSrc, float *pDst, float value)
{
    auto nThreads = std::thread::hardware_concurrency();
    std::list<std::thread> tlist;

    cnt = 0;
    size_t end=nData-nThreads;
    for (auto i=0; i<nThreads; ++i) {
        tlist.push_back(std::thread([=] { process(pSrc+i, pSrc+end+i,pDst+i,nThreads,value); }));
    }

    for (auto it=tlist.begin(); it!=tlist.end();++it)
        it->join();

    return 0;
}

int Processor::frun(float *pSrc, float *pDst, float *k, int nK)
{
    return filter(pSrc, pSrc+nData, pDst, k, nK);
}

int Processor::frunp(float *pSrc, float *pDst, float *k, int nK)
{
    auto nThreads = std::thread::hardware_concurrency();
    std::cout<<"frunp "<<nThreads<<" threads\n";
    size_t blockSize=nData / nThreads;
    std::list<std::thread> tlist;
    size_t begin=0;
    size_t end=blockSize;
    cnt = 0;
    for (auto i=0; i<nThreads; ++i) {
        tlist.push_back(std::thread([=] { filter(pSrc+begin, pSrc+end,pDst+begin,k,nK); }));
        begin+=blockSize;
        end+=blockSize;
    }

    for (auto & it: tlist)
        it.join();

    return 0;
}


int Processor::f2run(float *pSrc, float *pDst, float *k, int nK, size_t bSize)
{
    return filter(pSrc, pSrc+nData, pDst, k, nK,bSize);
}

int Processor::f2runp(float *pSrc, float *pDst, float *k, int nK, size_t bSize)
{
    auto nThreads = std::thread::hardware_concurrency();
    std::cout<<"frunp "<<nThreads<<" threads\n";
    size_t blockSize=nData / nThreads;
    std::list<std::thread> tlist;
    size_t begin=0;
    size_t end=blockSize;

    cnt = 0;

    for (auto i=0; i<nThreads; ++i) {
        tlist.push_back(std::thread([=] { filter(pSrc+begin, pSrc+end,pDst+begin,k,nK,bSize); }));
        begin+=blockSize;
        end+=blockSize;
    }

    for (auto & it: tlist)
        it.join();

    return 0;
}
int Processor::tester(size_t N)
{
    nData = N;



    data=new float[nData];
    dest1=new float[nData];
    dest2=new float[nData];
    dest3=new float[nData];

    for (size_t i=0; i<nData; ++i) {
        data[i]=static_cast<float>(i);
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    runp(data, dest1,5.0f);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto tduration=end_time - start_time;
    std::cout<<"runp\n";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(tduration).count() << "s : ";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tduration).count() << "us"<<std::endl;

//    start_time = std::chrono::high_resolution_clock::now();
//    runps(data, dest3,5.0f);

//    end_time = std::chrono::high_resolution_clock::now();

//    auto tsduration=end_time - start_time;
//    std::cout<<"runps\n";
//    std::cout << std::chrono::duration_cast<std::chrono::seconds>(tsduration).count() << "s : ";
//    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tsduration).count() << "us"<<std::endl;

//    start_time = std::chrono::high_resolution_clock::now();
//    run(data, dest2,5.0f);

//    end_time = std::chrono::high_resolution_clock::now();
//    auto sduration=end_time - start_time;
//    std::cout<<"run\n";
//    std::cout << std::chrono::duration_cast<std::chrono::seconds>(sduration).count() << "s : ";
//    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(sduration).count() << "us"<<std::endl;

//    std::cout<<"Speedup = "<<std::chrono::duration<float>(sduration)/
//                             std::chrono::duration<float>(tduration)<<std::endl;

//    for (size_t i=0; i<nData; ++i) {
//        if (dest1[i]!=dest2[i]) {
//            std::cout<<"Fail at i="<<i<<std::endl;

//            return -1;
//        }
//    }

    return 0;
}

int Processor::ftester(size_t N)
{
//#define ALLDATA
#define BLOCKEDDATA
    nData = N;

    data=new float[nData];
    dest1=new float[nData];
    dest2=new float[nData];
    dest3=new float[nData];

    for (size_t i=0; i<nData; ++i) {
        data[i]=static_cast<float>(i);
    }

    const int nK=27;
    float k[nK]={1,2,3,4,5,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9};
#ifdef ALLDATA
    {
    auto start_time = std::chrono::high_resolution_clock::now();
    frunp(data, dest1,k,nK);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto tduration=end_time - start_time;
    std::cout<<"runp\n";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(tduration).count() << "s : ";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tduration).count() << "us"<<std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    frun(data, dest2,k,nK);

    end_time = std::chrono::high_resolution_clock::now();
    auto sduration=end_time - start_time;
    std::cout<<"run\n";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(sduration).count() << "s : ";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(sduration).count() << "us"<<std::endl;

    std::cout<<"Speedup = "<<std::chrono::duration<float>(sduration)/
                             std::chrono::duration<float>(tduration)<<std::endl;
    }
#endif

#ifdef BLOCKEDDATA
    {
    // Blocked processing
    const size_t blockSize=1024;
    auto start_time = std::chrono::high_resolution_clock::now();
    f2runp(data, dest1,k,nK,blockSize);
    std::cout<<"cnt="<<cnt<<"\n";

    auto end_time = std::chrono::high_resolution_clock::now();
    auto tduration=end_time - start_time;
    std::cout<<"runp\n";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(tduration).count() << "s : ";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tduration).count() << "us"<<std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    f2run(data, dest2,k,nK,blockSize);
    std::cout<<"cnt="<<cnt<<"\n";

    end_time = std::chrono::high_resolution_clock::now();
    auto sduration=end_time - start_time;
    std::cout<<"run\n";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(sduration).count() << "s : ";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(sduration).count() << "us"<<std::endl;

    std::cout<<"Speedup = "<<std::chrono::duration<float>(sduration)/
                             std::chrono::duration<float>(tduration)<<std::endl;
    }
#endif
//    for (size_t i=0; i<nData; ++i) {
//        if (dest1[i]!=dest2[i]) {
//            std::cout<<"Fail at i="<<i<<std::endl;

//            return -1;
//        }
//    }

    return 0;
}

int Processor::process(float *srcStart, float *srcEnd, float *dst, float value)
{
    float *s=srcStart;
    float *d=dst;
    for (; s!=srcEnd; ++s, ++d)
    {
        (*d)+=powf((*s), value);
        ++cnt;
    }

    return 0;
}

int Processor::process(float *srcStart, float *srcEnd, float *dst, size_t stride,float value)
{
    for (float *s=srcStart,*d=dst; s!=srcEnd; s+=stride, d+=stride)
    {
        (*d)+=(*s) * value;
    }

    ++cnt;
    return 0;
}

int Processor::filter(float *srcStart, float *srcEnd, float *dst, float *k, int nK)
{
    float *s;
    float *d;

    for (int i=0; i<nK; ++i)
    {
        for (s=srcStart, d=dst; s!=srcEnd; ++s,++d)
        {
            (*d)+=(*s)*k[i];
        }
    }

    return 0;
}


int Processor::filter(float *srcStart, float *srcEnd, float *dst, float *k, int nK, size_t blockSize)
{
    size_t N=(srcEnd-srcStart)/blockSize;
    cnt = 0;
    for (size_t j=0; j<N; ++j)
    {
        float *s=srcStart+j*blockSize;
        float *d=dst+j*blockSize;

        for (int i=0; i<nK; ++i)
        {
            for (size_t m=0; m<blockSize; ++m)
            {
                d[m]+=s[m]*k[i];
            }
        }
        ++cnt;
    }

    return 0;
}
