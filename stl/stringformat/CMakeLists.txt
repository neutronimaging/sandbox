cmake_minimum_required(VERSION 3.5)

project(stringformat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(stringformat stringformat.cpp)

include(GNUInstallDirs)
install(TARGETS stringformat
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
