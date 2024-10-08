cmake_minimum_required(VERSION 3.10)
project(MetalComputeBasic)

set(TARGET MetalComputeBasic)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -ObjC++")

find_library(METAL_LIBRARY Metal)
find_library(FOUNDATION_LIBRARY Foundation)
find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
find_library(OBJC_LIBRARY objc)

# Assume your adder.metal file is in the same directory as your CMakeLists.txt file
set(METAL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/add.metal")
set(AIR_FILE "${CMAKE_CURRENT_BINARY_DIR}/adder.air")
set(METALLIB_FILE "${CMAKE_CURRENT_BINARY_DIR}/shader.metallib")

# Add a custom command to compile the .metal file to an .air file
add_custom_command(
    OUTPUT ${AIR_FILE}
    COMMAND xcrun -sdk macosx metal -c ${METAL_SOURCE} -o ${AIR_FILE}
    DEPENDS ${METAL_SOURCE}
    COMMENT "Compiling ${METAL_SOURCE}"
)

# Add a custom command to link the .air file to a .metallib file
add_custom_command(
    OUTPUT ${METALLIB_FILE}
    COMMAND xcrun -sdk macosx metallib ${AIR_FILE} -o ${METALLIB_FILE}
    DEPENDS ${AIR_FILE}
    COMMENT "Linking ${AIR_FILE}"
)

# Add a custom target to run the custom commands
add_custom_target(
    shader ALL
    DEPENDS ${METALLIB_FILE}
)

add_executable(${TARGET} main.m MetalAdder.m)

# Assume your shader.metallib file is in the same directory as your CMakeLists.txt file
# set(SHADER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/shader.metallib")
set(SHADER_PATH "${METALLIB_FILE}")
# Set the shader.metallib file as a resource
set_source_files_properties(${SHADER_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

# Add the shader.metallib file to your target
target_sources(${TARGET} PRIVATE ${SHADER_PATH})

target_link_libraries(${TARGET} ${METAL_LIBRARY} ${FOUNDATION_LIBRARY} ${CORE_FOUNDATION_LIBRARY} ${OBJC_LIBRARY})
# Set your target to be a bundle
set_target_properties(${TARGET} PROPERTIES MACOSX_BUNDLE TRUE)