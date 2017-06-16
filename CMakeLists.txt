cmake_minimum_required(VERSION 2.6.0)
project(sens-viewer)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++14")
set(LIBRARIES ${OpenCV_LIBRARIES})

#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(sens-viewer main.cpp)
#target_link_libraries(sens-viewer ...)

# Tell QtCreator to show these files
file(GLOB showfiles *.h *.md)
add_custom_target(showfiles SOURCES ${showfiles})

