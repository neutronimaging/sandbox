#ifndef PYBINDTEST_H
#define PYBINDTEST_H

#include "pybindtest_global.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

float PYBINDTESTSHARED_EXPORT add(float i, float j);
#endif // PYBINDTEST_H
