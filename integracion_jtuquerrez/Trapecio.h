#ifndef TRAPECIO_H
#define TRAPECIO_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Expression.h"
#include "util.h"

using std::string;
using std::vector;

using util::crear_tabla;

namespace integracion {
    /**
     * @brief Integracion mediante el metodo del trapecio
     */
    class trapecio {
        public:
            /**
             * @brief Constructor de la clase
             * @param p_fn Funcion a integrar
             */
            explicit trapecio(string p_fn):str_fn(p_fn){    }

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

                crear_tabla(x, y, a, b, n, str_fn);

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
                    sum += fabs(y[i]);
                }

                double coef = fabs(y[0]) + (2.0f*sum) + fabs(y[n]);

                return (x[n] - x[0]) * (coef / (2.0f*n));
            }
    private:
        string str_fn; /*< Evaluador de la funcion */
    };
}

#endif
