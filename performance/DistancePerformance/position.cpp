#include "position.h"
#include <algorithm>
#include <pmmintrin.h>

Position::Position()
{
    std::fill_n(pos.v,4,0);
}

Position::Position(float x, float y, float z)
{
    pos.v[0]=x;
    pos.v[1]=y;
    pos.v[2]=z;
    pos.v[3]=0.0;
}

float dist(Position &a, Position &b)
{
    return (a.pos.c.x-b.pos.c.x)*(a.pos.c.x-b.pos.c.x)
            +(a.pos.c.y-b.pos.c.y)*(a.pos.c.y-b.pos.c.y)
            +(a.pos.c.z-b.pos.c.z)*(a.pos.c.z-b.pos.c.z);
}

float distSSE(Position &a, Position &b)
{
    __m128 diff,tmp;

    diff=_mm_sub_ps(a.pos.reg,b.pos.reg);
    diff=_mm_hadd_ps(_mm_hadd_ps(_mm_mul_ps(diff,diff),tmp),tmp);
//  diff=_mm_hadd_ps(_mm_hadd_ps(_mm_mul_ps(_mm_sub_ps(a.pos.reg,b.pos.reg),_mm_sub_ps(a.pos.reg,b.pos.reg)),tmp),tmp);

    return reinterpret_cast<float *>(&diff)[0];
}
