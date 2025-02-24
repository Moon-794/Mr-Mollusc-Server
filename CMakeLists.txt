cmake_minimum_required(VERSION 3.6.0)
project (mrmollusc)

set(CMAKE_PREFIX_PATH "/mingw64")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_executable(mrmollusc ../src/main.cpp)

find_package(SDL2 REQUIRED COMPONENTS SDL2)

target_include_directories(mrmollusc PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(mrmollusc PRIVATE SDL2::SDL2 ws2_32)