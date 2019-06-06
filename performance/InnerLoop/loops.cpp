#include <emmintrin.h>
#include "loops.h"

#include <algorithm>
#include <thread>
#include <future>
#include <vector>
#include <list>


void tunedLoop(float *src, float *dest, float value, int N);
void originalLoop(float *src, float * dest, float value, int N);
void stlLoop(float *src, float * dest, float value, int N);

Loops::Loops(int N) :
    data(new float[N]),
    result(new float[N]),
    nData(N)
{
    for (int i=0; i<N; ++i)
        data[i]=static_cast<float>(i);

    std::fill_n(result,N,1.2345f);
}

Loops::~Loops()
{
    delete [] data;
    delete [] result;
}

void Loops::original()
{
    originalLoop(data,result,20.0f,nData);
}

void Loops::tuned()
{
    tunedLoop(data,result,20.0f,nData);
}

void Loops::threaded()
{
    threadLoop(data,result,20.0f,nData);
}

void Loops::async()
{
    threadLoop(data,result,20.0f,nData);
}

void Loops::parallelSTL()
{
    stlLoop(data,result,20.0,nData);
}



void Loops::threadLoop(float *src, float * dest, float value, int N)
{
    auto nThreads = static_cast<int>(std::thread::hardware_concurrency());
    int blockSize=N / nThreads;
    blockSize-=blockSize % 4;

    std::list<std::thread> tlist;
    int begin=0;

    for (auto i=0; i<nThreads; ++i) {
        tlist.push_back(std::thread([=] { tunedLoop(src+begin,dest+begin,value, blockSize); }));

        begin+=blockSize;

    }

    for (auto it=tlist.begin(); it!=tlist.end();++it)
        it->join();
}

void Loops::asyncLoop(float *src, float * dest, float value, int N)
{
    auto nThreads = static_cast<int>(std::thread::hardware_concurrency());
    int blockSize=nData / nThreads;
    blockSize-=blockSize % 4;

    int begin=0;

    for (auto i=0; i<nThreads; ++i) {
        std::async(std::launch::async,tunedLoop,src+begin,dest+begin,value, blockSize);
        begin+=blockSize;
    }

}

void Loops::stlLoop(float *src, float * dest, float value, int N)
{

//    auto p = std::execution::par;
//    std::for_each(p, indices.begin(), indices.end(), [&mice](size_t i)
//        {
//            if (i == 0) mice[i] += " is first.";
//            else if (i + 1 == mice.size()) mice[i] += " is last.";
//        }
//    );
}

void originalLoop(float *src, float * dest, float value, int N)
{
    for (int j=0; j<N; j++) {
        dest[j]+=src[j]*value;
    }
}

void tunedLoop(float *src, float *dest, float value, int N)
{
    int N4=N/4;

    __m128 * src128 = reinterpret_cast<__m128 *>(src);
    __m128 * dest128 = reinterpret_cast<__m128 *>(dest);

    __m128 val128=_mm_set1_ps(value);
    __m128 *pEnd=src128+N4;

    for (auto s=src128, d=dest128; s!=pEnd; ++s,++d) {
        //dest[j]+=src[j]*value;
        *d=_mm_add_ps(*d,_mm_mul_ps(*s,val128));

    }
}
