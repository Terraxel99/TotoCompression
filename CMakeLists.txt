cmake_minimum_required(VERSION 2.8)
project(TotoCompression)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(TotoCompression src/main.cpp)
set_target_properties(TotoCompression PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

target_link_libraries(TotoCompression ${OpenCV_LIBS})