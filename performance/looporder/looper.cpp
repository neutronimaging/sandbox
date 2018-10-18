#include "looper.h"

looper::looper()
{

}

void looper::fillImageA(size_t N)
{
    size_t dims[2]={N,N};

    imgA.Resize(dims);
    imgB.Resize(dims);

    for (size_t i=0; i<imgA.Size(); ++i)
        imgA[i]=static_cast<float>(i);

    imgB=0.0f;
}

void looper::loopxyOp()
{
   for (size_t x=0; x<imgA.Size(0); x++)
       for (size_t y=0; y<imgA.Size(1); y++)
           imgB(x,y)=imgA(x,y)*(x+y);
}

void looper::loopyxOp()
{
    for (size_t y=0; y<imgA.Size(1); y++)
        for (size_t x=0; x<imgA.Size(0); x++)
            imgB(x,y)=imgA(x,y)*(x+y);
}

void looper::loopyxPtr()
{
    size_t idx=0;
    float *pA=imgA.GetDataPtr();
    float *pB=imgB.GetDataPtr();
    for (size_t y=0; y<imgA.Size(1); ++y)
        for (size_t x=0; x<imgA.Size(0); ++x,++idx)
            pB[idx]=pA[idx]*(x+y);
}

void looper::loopyxPtr2()
{
    size_t idx=0;
    float *pA=imgA.GetDataPtr();
    float *pB=imgB.GetDataPtr();
    for (size_t y=0; y<imgA.Size(1); ++y)
        for (size_t x=0; x<imgA.Size(0); ++x, ++pA, ++pB)
            (*pB)=(*pA)*(x+y);
}
