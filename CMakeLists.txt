cmake_minimum_required(VERSION 3.24)
project(MiniGolf)

set(CMAKE_CXX_STANDARD 11)

add_executable(MiniGolf main.cpp GeoDraw.cpp GeoDraw.h types.h graphics.cpp graphics.h game.cpp game.h physics.cpp physics.h animation.cpp animation.h)
