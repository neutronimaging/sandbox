#ifndef PYBINDTEST_H
#define PYBINDTEST_H

//#include "pybindtest_global.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

//int PYBINDTESTSHARED_EXPORT add(int i, int j);


int add(int i, int j);
#endif // PYBINDTEST_H
