cmake_minimum_required(VERSION 3.30)
project(binding_latency_benchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)

execute_process(
    COMMAND ${Python_EXECUTABLE} -m nanobind --cmake_dir
    OUTPUT_VARIABLE nanobind_ROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

list(APPEND CMAKE_PREFIX_PATH "${nanobind_ROOT}")

find_package(pybind11 CONFIG REQUIRED)
find_package(nanobind CONFIG REQUIRED)

add_library(add_core INTERFACE)
target_include_directories(add_core INTERFACE src)

pybind11_add_module(pybind_add src/pybind_add.cpp)
target_link_libraries(pybind_add PRIVATE add_core)

nanobind_add_module(nanobind_add src/nanobind_add.cpp)
target_link_libraries(nanobind_add PRIVATE add_core)

nanobind_add_module(cpp_add src/cpp_add.cpp)
target_link_libraries(cpp_add PRIVATE add_core)