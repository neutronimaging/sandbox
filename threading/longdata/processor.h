#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include <atomic>

class Processor
{
public:
    Processor();
    ~Processor();

    int run(float *pSrc, float *pDst, float value);
    int runp(float *pSrc, float *pDst, float value);
    int runps(float *pSrc, float *pDst,float value);
    int frun(float *pSrc, float *pDst,float *k, int nK);
    int frunp(float *pSrc, float *pDst,float *k, int nK);
    int f2run(float *pSrc, float *pDst, float *k, int nK, size_t bSize);
    int f2runp(float *pSrc, float *pDst, float *k, int nK, size_t bSize);
    int tester(size_t N);
    int ftester(size_t N);

    std::atomic_int cnt;
protected:
    int process(float *srcStart, float *srcEnd, float *dst, float value);
    int process(float *srcStart, float *srcEnd, float *dst, size_t stride,float value);
    int filter(float *srcStart, float *srcEnd, float *dst, float *k, int nK);
    int filter(float *srcStart, float *srcEnd, float *dst, float *k, int nK, size_t blockSize);
    size_t nData;
    float *data;
    float *dest1;
    float *dest2;
    float *dest3;

};

#endif // PROCESSOR_H
