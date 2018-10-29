#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>

class Processor
{
public:
    Processor();
    ~Processor();

    int run(float *pSrc, float *pDst, float value);
    int runp(float *pSrc, float *pDst, float value);
    int runps(float *pSrc, float *pDst,float value);
    int tester(size_t N);

protected:
    int process(float *srcStart, float *srcEnd, float *dst, float value);
    int process(float *srcStart, float *srcEnd, float *dst, size_t stride,float value);
    size_t nData;
    float *data;
    float *dest1;
    float *dest2;
    float *dest3;
};

#endif // PROCESSOR_H
