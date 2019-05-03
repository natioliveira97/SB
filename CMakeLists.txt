cmake_minimum_required(VERSION 2.8)
project(Montador)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(tradutor main.cpp pre_processor.cpp pre_processor.hpp)

