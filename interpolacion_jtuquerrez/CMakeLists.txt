cmake_minimum_required(VERSION 3.26)
project(interpolacion_jtuquerrez)

set(CMAKE_CXX_STANDARD 17)

add_executable(interpolacion_jtuquerrez main.cpp
        newton.h
        util.h
        lagrange.h
        spline3.h
        spline3.h)
