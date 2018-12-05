#include "pybindtest_global.h"
#include "pybindtest.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

float PYBINDTESTSHARED_EXPORT add(float i, float j)
{
    return i + j;
}

PYBINDTESTSHARED_EXPORT adder::adder(float a, float b):
    ma(a),
    mb(b)
{}

void PYBINDTESTSHARED_EXPORT adder::setValues(float a, float b)
{
    ma=a;
    mb=b;
}

float PYBINDTESTSHARED_EXPORT adder::sum()
{
    return ma+mb;
}

class Matrix
{
public:
    Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols) {
        m_data = new float[rows*cols];
        for (size_t i=0; i<rows*cols; ++i) {
            m_data[i]=static_cast<float>(i);
        }
    }
    float *data() { return m_data; }
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }
private:
    size_t m_rows, m_cols;
    float *m_data;
};

struct  PYBINDTESTSHARED_EXPORT Pet {
    Pet(const std::string &name) : name(name) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

    std::string name;
};


py::array_t<double> add_arrays(py::array_t<double> input1, py::array_t<double> input2) {
   /* read input arrays buffer_info */
   py::buffer_info buf1 = input1.request(), buf2 = input2.request();
   if (buf1.size != buf2.size)
      throw std::runtime_error("Input shapes must match");

   /* allocate the output buffer */
   py::array_t<double> result = py::array_t<double>(buf1.size);
   py::buffer_info buf3 = result.request();
   double *ptr1 = (double *) buf1.ptr, *ptr2 = (double *) buf2.ptr, *ptr3 = (double *)buf3.ptr;
   size_t X = buf1.shape[0];
   size_t Y = buf1.shape[1];

   /* Add both arrays */
   for (size_t idx = 0; idx < X; idx++)
       for (size_t idy = 0; idy < Y; idy++)
           ptr3[idx*Y + idy] = ptr1[idx*Y+ idy] + ptr2[idx*Y+ idy];

   /* Reshape result to have same shape as input */
   result.resize({X,Y});

   return result;
}


PYBIND11_MODULE(pybindtest,m) {

    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.def("add", &add, "A function which adds two numbers");

    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName);

    py::class_<adder>(m, "adder")
        .def(py::init<float,float>())
        .def("setValues", &adder::setValues)
        .def("sum", &adder::sum);

    py::class_<Matrix>(m, "Matrix", py::buffer_protocol())
       .def_buffer([](Matrix &m) -> py::buffer_info {
            return py::buffer_info(
                m.data(),                               /* Pointer to buffer */
                sizeof(float),                          /* Size of one scalar */
                py::format_descriptor<float>::format(), /* Python struct-style format descriptor */
                2,                                      /* Number of dimensions */
                { m.rows(), m.cols() },                 /* Buffer dimensions */
                { sizeof(float) * m.rows(),             /* Strides (in bytes) for each index */
                  sizeof(float) }
            );
        })
        .def(py::init<size_t,size_t>())
        .def("rows", &Matrix::rows)
        .def("cols", &Matrix::cols)
        .def("data", &Matrix::data);

    m.def("add_arrays", &add_arrays, "Add two NumPy arrays");
}
