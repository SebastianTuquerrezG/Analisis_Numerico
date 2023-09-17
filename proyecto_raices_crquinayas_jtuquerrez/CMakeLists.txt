cmake_minimum_required(VERSION 3.26)
project(proyecto_raices_crquinayas_jtuquerrez)

set(CMAKE_CXX_STANDARD 17)

add_executable(proyecto_raices_crquinayas_jtuquerrez main.cpp
        muller.h
        biseccion.h
        Expression.h
        newton_generalizado.h
        newton_raphson.h
        reglafalsa.h
        secante.h
        solucion.h)
