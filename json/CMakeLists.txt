cmake_minimum_required(VERSION 3.24)
project(json_demo LANGUAGES CXX)

# Your preference
set(CMAKE_CXX_STANDARD 22)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Let CMake find Conan-generated config files
# (CMakeDeps generator produces nlohmann_jsonConfig.cmake)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(json_demo src/main.cpp)
target_link_libraries(json_demo PRIVATE nlohmann_json::nlohmann_json)

# Nice warnings (optional)
if (MSVC)
  target_compile_options(json_demo PRIVATE /W4 /permissive-)
else()
  target_compile_options(json_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()

