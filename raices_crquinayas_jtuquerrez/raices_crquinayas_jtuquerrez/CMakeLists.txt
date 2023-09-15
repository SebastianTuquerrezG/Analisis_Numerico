cmake_minimum_required(VERSION 3.25)
project(raices_crquinayas_jtuquerrez)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(raices_crquinayas_jtuquerrez
        biseccion.h
        Expression.h
        main.cpp
        newton_raphson.h
        reglafalsa.h
        solucion.h newton_generalizado.h secante.h)
