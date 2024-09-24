cmake_minimum_required(VERSION 3.6.0)
project (mrmollusc)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_executable(mrmollusc ../src/main.cpp)

target_include_directories(mrmollusc PRIVATE ${CMAKE_SOURCE_DIR}/include/PDCurses)
target_link_libraries(mrmollusc ${CMAKE_SOURCE_DIR}/lib/pdcurses.a)