cmake_minimum_required(VERSION 3.20)
project(MetalSumAxis LANGUAGES C CXX OBJCXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")

set(METAL_SHADER metal_sum_axis.metal)
set(METALLIB metal_sum_axis.metallib)
set(METAL_AIR metal_sum_axis.air)

# Step 1: Custom command to compile .metal -> .air -> .metallib
add_custom_command(
    OUTPUT ${METALLIB}
    COMMAND xcrun -sdk macosx metal -c ${CMAKE_CURRENT_SOURCE_DIR}/${METAL_SHADER} -o ${METAL_AIR}
    COMMAND xcrun -sdk macosx metallib ${METAL_AIR} -o ${METALLIB}
    DEPENDS ${METAL_SHADER}
    COMMENT "Compiling Metal shader to ${METALLIB}"
    VERBATIM
)

# Step 2: Custom target to represent the .metallib build
add_custom_target(MetalLib ALL DEPENDS ${METALLIB})

# Step 3: Build C++ host executable
add_executable(metal_host metal_host.cpp)
add_dependencies(metal_host MetalLib)

target_link_libraries(metal_host
    "-framework Metal"
    "-framework Foundation"
)

set_target_properties(metal_host PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
