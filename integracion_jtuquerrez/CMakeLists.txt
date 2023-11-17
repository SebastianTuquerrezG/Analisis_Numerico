cmake_minimum_required(VERSION 3.26)
project(integracion_jtuquerrez)

set(CMAKE_CXX_STANDARD 17)

add_executable(integracion_jtuquerrez main.cpp
        Expression.h
        Trapecio.h
        util.h
        SimpsonTercio.h
        Simpson38.h)
