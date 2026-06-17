cmake_minimum_required(VERSION 3.24)
project(QtVolumeRenderer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.8 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)
qt_add_executable(QtVolumeRenderer
    src/main.cpp
    src/VolumeRenderWidget.cpp
    src/VolumeRenderWidget.h
    src/VolumeViewerWidget.cpp
    src/VolumeViewerWidget.h
    resources.qrc
)

target_link_libraries(QtVolumeRenderer PRIVATE
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)

if(APPLE)
    set_target_properties(QtVolumeRenderer PROPERTIES
        MACOSX_BUNDLE FALSE
    )
endif()
