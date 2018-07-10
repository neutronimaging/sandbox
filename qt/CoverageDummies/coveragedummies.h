#ifndef COVERAGEDUMMIES_H
#define COVERAGEDUMMIES_H

#include "coveragedummies_global.h"

class COVERAGEDUMMIESSHARED_EXPORT CoverageDummies
{

public:
    CoverageDummies();
    int get();
    void set(int x);
    int decade();
protected:
    int val;

};

#endif // COVERAGEDUMMIES_H
