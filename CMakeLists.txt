cmake_minimum_required(VERSION 3.10)
project(KeyKG)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_compile_options(-Wall -Wextra -Wconversion -Wshadow -fdiagnostics-color=always)

add_subdirectory(Utils)
add_subdirectory(Main)
