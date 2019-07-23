#include "crosscorrelation.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <list>

CrossCorrelation::CrossCorrelation()
{

}

float CrossCorrelation::operator()(float *x, float *y, size_t N, bool parallel)
{
    mN = N;
    if (parallel)
        mSums=computeSumsParallel(x,y,N);
    else
        mSums=computeSums(x,y,N);

    float &sx  = mSums[0];
    float &sy  = mSums[1];
    float &sx2 = mSums[2];
    float &sy2 = mSums[3];
    float &sxy = mSums[4];

    float ssxx  = sx2 - sx*sx/N;
    float ssyy  = sy2 - sy*sy/N;
    float ss2xy = sxy - sx*sy/N;
    ss2xy = ss2xy * ss2xy;

    float r = ss2xy/(ssxx*ssyy);

    return r;
}

std::vector<float> CrossCorrelation::computeSums(float *x, float *y, size_t N)
{
    std::vector<float> sums(5);

    float &sx = sums[0];
    float &sy = sums[1];
    float &sx2 = sums[2];
    float &sy2 = sums[3];
    float &sxy = sums[4];

    for (size_t i = 0UL; i<N; ++i)
    {
        sx  += x[i];
        sx2 += x[i]*x[i];
        sxy += x[i]*y[i];
        sy  += y[i];
        sy2 += y[i]*y[i];
    }

    return sums;
}



std::vector<float> CrossCorrelation::computeSumsParallel(float *x, float *y, size_t N)
{
    std::vector<float> sums(5);

    auto nThreads    = std::thread::hardware_concurrency();
    size_t blockSize = N / nThreads;
    std::list<std::thread> tlist;
    size_t begin=0;

    for (unsigned int i=0; i<nThreads; ++i) {
        tlist.push_back(std::thread([=] { computeSums(x+begin, y+begin,blockSize); }));
        begin+=blockSize;
    }

    for (auto &it: tlist)
        it.join();


    return sums;
}
