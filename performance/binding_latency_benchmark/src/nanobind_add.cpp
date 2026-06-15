#include <nanobind/nanobind.h>
#include "add.hpp"

namespace nb = nanobind;

NB_MODULE(nanobind_add, m) {
    m.doc() = "nanobind add latency test module";
    m.def("add", &add, nb::arg("a"), nb::arg("b"));
}
