cmake_minimum_required(VERSION 2.8)
project(TotoCompression)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    src/main.cpp
    src/image/TotoImage.cpp
    src/image/TotoBlock.cpp
    src/image/TotoCompressionMeasure.cpp
    src/video/TotoVideo.cpp
    src/video/TotoIVideo.cpp
    src/video/TotoDVideo.cpp
    src/view/TotoConsoleOutput.cpp)

add_executable(TotoCompression ${SOURCE_FILES})

set_target_properties(TotoCompression PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
target_link_libraries(TotoCompression ${OpenCV_LIBS})