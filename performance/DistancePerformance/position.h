#ifndef POSITION_H
#define POSITION_H

#include <emmintrin.h>

typedef union
{
    __m128i reg;
    struct {
        float x;
        float y;
        float z;
        float res;
    } c;
    float v[4];

} regval;

class Position
{
public:
    Position();
    Position(float x, float y, float z);

    regval pos;
};

float dist(Position &a, Position &b);

float distSSE(Position &a, Position &b);

#endif // POSITION_H
