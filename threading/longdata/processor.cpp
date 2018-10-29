#include <thread>
#include <chrono>
#include <iostream>
#include <list>

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
    size_t blockSize=nData / nThreads;
    std::list<std::thread> tlist;
    size_t begin=0;
    size_t end=blockSize;
    for (auto i=0; i<nThreads; ++i) {
        tlist.push_back(std::thread([=] { process(pSrc+begin, pSrc+end,pDst+begin,value); }));
        begin+=blockSize;
        end+=blockSize;
    }

    for (auto it=tlist.begin(); it!=tlist.end();++it)
        it->join();

    return 0;
}

int Processor::runps(float *pSrc, float *pDst, float value)
{
    auto nThreads = std::thread::hardware_concurrency();
    std::list<std::thread> tlist;

    size_t end=nData-nThreads;
    for (auto i=0; i<nThreads; ++i) {
        tlist.push_back(std::thread([=] { process(pSrc+i, pSrc+end+i,pDst+i,nThreads,value); }));
    }

    for (auto it=tlist.begin(); it!=tlist.end();++it)
        it->join();

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
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(tduration).count() << "s : ";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tduration).count() << "us"<<std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    runps(data, dest3,5.0f);

    end_time = std::chrono::high_resolution_clock::now();

    auto tsduration=end_time - start_time;
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(tsduration).count() << "s : ";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tsduration).count() << "us"<<std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    run(data, dest2,5.0f);

    end_time = std::chrono::high_resolution_clock::now();
    auto sduration=end_time - start_time;
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(sduration).count() << "s : ";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(sduration).count() << "us"<<std::endl;

    std::cout<<"Speedup = "<<std::chrono::duration<float>(sduration)/
                             std::chrono::duration<float>(tduration)<<std::endl;

    for (size_t i=0; i<nData; ++i) {
        if (dest1[i]!=dest2[i]) {
            std::cout<<"Fail at i="<<i<<std::endl;

            return -1;
        }
    }

    return 0;
}

int Processor::process(float *srcStart, float *srcEnd, float *dst, float value)
{
    for (float *s=srcStart,*d=dst; s!=srcEnd; ++s, ++d)
    {
        (*d)+=(*s) * value;
    }

    return 0;
}

int Processor::process(float *srcStart, float *srcEnd, float *dst, size_t stride,float value)
{
    for (float *s=srcStart,*d=dst; s!=srcEnd; s+=stride, d+=stride)
    {
        (*d)+=(*s) * value;
    }

    return 0;
}
