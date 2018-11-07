#include "pybindtest_global.h"
#include "pybindtest.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

float PYBINDTESTSHARED_EXPORT add(float i, float j)
{
    return i + j;
}

PYBIND11_MODULE(pybindtest,m) {

    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.def("add", &add, "A function which adds two numbers");
}
