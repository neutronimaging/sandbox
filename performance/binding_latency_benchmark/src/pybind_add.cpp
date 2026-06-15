#include <pybind11/pybind11.h>
#include "add.hpp"

namespace py = pybind11;

PYBIND11_MODULE(pybind_add, m) {
    m.doc() = "pybind11 add latency test module";
    m.def("add", &add, py::arg("a"), py::arg("b"));
}
