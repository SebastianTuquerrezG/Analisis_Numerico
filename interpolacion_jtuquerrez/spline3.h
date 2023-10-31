#ifndef SPLINE3_H
#define SPLINE3_H

#include <vector>
#include <utility>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>

#include "util.h"
#include "newton.h"

using std::vector;
using std::pair;
using std::string;
using std::ostringstream;
using std::cout;
using std::cin;
using std::endl;

using util::gauss;
using util::imprimit_matriz;
using util::str_repeat;

namespace interpolacion{
    class spline3{
    public:
        spline3(vector<double> p_x, vector<double> p_y):x(std::move(p_x)), y(std::move(p_y)){
            //Calcular las segundas derivadas
            f2 = calcular_f2();
        }

        double interpolar(double x_int){
            //TODO: Determinar el intervalo i en donde se encuentra x_int
            size_t i = 0;
            for(i = 0; i < x.size(); i++){
                if(x_int < x[i]){
                    break;
                }
            }


            //TODO:
            // Evaluar el polinomio del trazador en x_int
            return NAN;
        }
    private:
        vector<double> x;
        vector<double> y;
        vector<double> f2;
        vector<double> calcular_f2(){
            vector<double> f2;

            size_t n = x.size(), i;
            size_t intervalos = n - 1;
            //TODO:
            // 1. Construir la matriz de coeficientes m
            // m es una matriz de banda, en donde:
            // En los puntos interiores, se tienen tres coeficientes
            // En el primer punto se tienen dos coeficientes
            // En el último punto se tienen dos coeficientes
            // m . f2 = c producto punto
            // c = Terminos a la derecha del igual de la ecuacion o los coeficientes que acompañan a las segundas derivadas

            vector<vector<double>> m(intervalos - 1);
            for(i = 0; i < intervalos - 1; i++){
                m[i].resize(n);
            }

            for(i = 1; i < intervalos; i++){
                size_t fila = i - 1;
                //Primer coeficiente
                if (i > 1){
                    //Los puntos interiores tienen f´´(xi -1)
                    m[fila][i - 1] = (x[i] - x[i - 1]);
                }
                //Segundo coeficiente
                m[fila][i] = 2.0f*(x[i + 1] - x[i-1]);
                if(i < intervalos - 1){
                    //Tercer coeficiente
                    //Los puntos interiores tienen f´´(xi + 1)
                    m[fila][i+1] = (x[i + 1] - x[i]);
                }

                //Terminos a la derecha
                double ci1 = (6/(x[i + 1] - x[i]))*(y[i + 1] - y[i]);

                double ci2 = (6/(x[i] - x[i - 1]))*(y[i - 1] - y[i]);

                double ci = ci1 + ci2;

                m[fila][intervalos] = ci;
            }

            //Imprimir matriz

            cout << "Coeficientes del sistema de ecuaciones"<< endl;
            cout << str_repeat("_", 40) << endl;
            //Eliminar la primera columna que contiene 0s
            for(i = 0; i < intervalos - 1; i++){
                m[i].erase(m[i].begin());
            }
            imprimit_matriz(m);

            cout << str_repeat("_", 40) << endl;
            //TODO:
            // 2. Calcular f2, f2 = gauss

            f2 = gauss(m);

            //Imprimir el vector resultado f2
            cout << "Segundas derivadas" << endl;
            for (int j = 0; j < f2.size(); ++j) {
                cout << "f2[" << j << "] = " << f2[j] << endl;
            }

            //TODO:
            // 2.1 Inservar 0 al inicio y al final de f2
            //  (f2 en los extremos vale 0)
            f2.insert(f2.begin(), 0);
            f2.insert(f2.end(), 0);

            return f2;
        }
    };
}

#endif
