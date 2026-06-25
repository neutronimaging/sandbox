#include <nanobind/nanobind.h>
#include "add.hpp"

namespace nb = nanobind;

NB_MODULE(cpp_add, m) {
    m.doc() = "nanobind add latency test module";
    m.def("add", &add_loop, nb::arg("n"), nb::arg("a"), nb::arg("b"), "Add two numbers in a loop");
}
