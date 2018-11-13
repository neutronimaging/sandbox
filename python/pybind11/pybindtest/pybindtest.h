#ifndef PYBINDTEST_H
#define PYBINDTEST_H

#include "pybindtest_global.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

float PYBINDTESTSHARED_EXPORT add(float i, float j);

class PYBINDTESTSHARED_EXPORT adder
{
public:
    adder(float a, float b);
    void setValues(float a, float b);
    float sum();
private:
    float ma;
    float mb;
};


#endif // PYBINDTEST_H
