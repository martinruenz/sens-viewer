cmake_minimum_required(VERSION 2.6.0)
project(sens-viewer)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++14")

add_executable(sens-viewer main.cpp)
target_link_libraries(sens-viewer ${OpenCV_LIBRARIES})

