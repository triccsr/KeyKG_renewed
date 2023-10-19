cmake_minimum_required(VERSION 3.10)
project(KeyKG)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

#set(CMAKE_CXX_FLAGS "-O2")

add_compile_options(-Wall -Wextra -Wconversion -Wshadow -fdiagnostics-color=always)

add_subdirectory(Main)
