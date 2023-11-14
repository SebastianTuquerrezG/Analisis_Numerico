#ifndef TRAPECIO_H
#define TRAPECIO_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Expression.h"

using std::string;
using std::vector;

namespace integracion {
    /**
     * @brief Integracion mediante el metodo del trapecio
     */
    class trapecio {
        public:
            /**
             * @brief Constructor de la clase
             * @param str_fn Funcion a integrar
             */
            explicit trapecio(string str_fn):f(str_fn){    }

            void crear_tabla(vector<double> &x,
                             vector<double> &y,
                             double a,
                             double b,
                             int n){
                x.resize(n + 1);
                y.resize(n + 1);

                //Calcular el paso
                double h = (b - a) / (double) n;
                double xi = a;

                for (int i = 0; i <= n; i++) {
                    x[i] = xi;
                    y[i] = f(xi);
                    xi += h;
                }
            }

            /**
             * @brief Calcula la integral
             * @param a limite inferior
             * @param b limite superior
             * @param n cantidad de segmentos
             * @return valor de la integral
             */
             double calcular(double a, double b, int n){
                if (n == 0) return NAN;
                if(a > b) std::swap(a , b);

                vector<double> x;
                vector<double> y;

                crear_tabla(x, y, a, b, n);

                return calcular(x, y);
            }

            /**
             * @brief Calcula la integral de una tabla de datos
             * @param x valores de la variable independiente
             * @param y valores de la variable dependiente
             * @return valor aproximado de la integral
             */
            double calcular(vector<double> &x,
                           vector<double> &y){
                size_t n = x.size() - 1;
                if(n <= 0) return NAN;

                double sum = 0.0f;

                for (size_t i = 1; i < n; i++) {
                    sum += y[i];
                }

                double coef = y[0] + (2.0f*sum) + y[n];

                return (x[n] - x[0]) * (coef / (2.0f*n));
            }
    private:
        Expression f; /*< Evaluador de la funcion */
    };
}

#endif
