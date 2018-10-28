#include <emmintrin.h>
#include "loops.h"

#include <algorithm>
#include <thread>
#include <vector>
#include <list>

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
    orignalLoop(data,result,20.0f,nData);
}

void Loops::tuned()
{
    tunedLoop(data,result,20.0f,nData);
}

void Loops::threaded()
{
    threadLoop(data,result,20.0f,nData);
}

void Loops::orignalLoop(float *src, float * dest, float value, int N)
{
    for (int j=0; j<N; j++) {
        dest[j]+=src[j]*value;
    }
}

void Loops::threadLoop(float *src, float * dest, float value, int N)
{
    auto nThreads = static_cast<int>(std::thread::hardware_concurrency());
    int blockSize=nData / nThreads;
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

void Loops::tunedLoop(float *src, float *dest, float value, int N)
{
    int N4=N/4;

    __m128 * src128 = reinterpret_cast<__m128 *>(src);
    __m128 * dest128 = reinterpret_cast<__m128 *>(dest);

    __m128 val128=_mm_set1_ps(value);

    for (int j=0; j<N4; ++j,++dest128,++src128) {
        //dest[j]+=src[j]*value;
        *dest128=_mm_add_ps(*dest128,_mm_mul_ps(*src128,val128));
    }
}
