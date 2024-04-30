cmake_minimum_required(VERSION 3.6.0)
project (mrmollusc)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_executable(mrmollusc ../src/main.cpp)

find_package(X11 REQUIRED)

include_directories(${X11_INCLUDE_DIR})
target_link_libraries(mrmollusc ${X11_LIBRARIES})

