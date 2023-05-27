cmake_minimum_required(VERSION 2.8)
project(TotoCompressionBenchmarking)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    src/main.cpp
    src/image/TotoImage.cpp
    src/image/TotoBlock.cpp
    src/image/TotoCompressionMeasure.cpp
    src/video/TotoIVideo.cpp
    src/operations/TotoOperationHandler.cpp
    src/view/TotoConsoleOutput.cpp)

add_executable(TotoCompressionBenchmarking ${SOURCE_FILES})

set_target_properties(TotoCompressionBenchmarking PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
target_link_libraries(TotoCompressionBenchmarking ${OpenCV_LIBS})