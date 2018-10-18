#ifndef LOOPER_H
#define LOOPER_H

#include <base/timage.h>

class looper
{
public:
    looper();
    void fillImageA(size_t N);
    void loopxyOp();
    void loopyxOp();
    void loopyxPtr();
    void loopyxPtr2();
    kipl::base::TImage<float,2> imgA;
    kipl::base::TImage<float,2> imgB;

};

#endif // LOOPER_H
