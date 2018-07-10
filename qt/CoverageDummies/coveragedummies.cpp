#include "coveragedummies.h"


CoverageDummies::CoverageDummies() :
    val(0)
{
}

int CoverageDummies::get()
{
    return val;
}

void CoverageDummies::set(int x)
{
    val = x;
}

int CoverageDummies::decade()
{
    if (val<0)
        return -1;

    if (30<val)
        return 30;
    if (20<val)
        return 20;

    if (10<val)
        return 10;

    return 0;
}
