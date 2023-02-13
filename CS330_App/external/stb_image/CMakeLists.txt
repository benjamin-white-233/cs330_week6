set(CMAKE_CXX_STANDARD 20)

cmake_minimum_required(VERSION 3.21)
project(stb)

add_library(stb stb.cpp)

target_include_directories(stb
    PUBLIC
        stb/
)