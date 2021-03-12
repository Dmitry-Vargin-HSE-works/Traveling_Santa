cmake_minimum_required(VERSION 3.17)
project(Traveling_Santa)

set(CMAKE_CXX_STANDARD 20)

add_executable(Traveling_Santa src/main.cpp src/Traveling_Santa.cpp include/Traveling_Santa.h include/Path.h)