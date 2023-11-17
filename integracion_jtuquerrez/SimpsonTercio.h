#ifndef SIMSONTERCIO_H
#define SIMSONTERCIO_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Expression.h"
#include "util.h"

using std::string;
using std::vector;

using util::crear_tabla;

namespace integracion{
    /**
     * @brief Integracion mediante el metodo de Simpson 1 tercio
     */
    class simpson13{
    public:
        /**
         * @brief Constructor de la clase
         * @param p_fn Funcion a integrar
         */
        explicit simpson13(string p_fn):str_fn(p_fn){}

        double calcular(double a, double b, int n){
            if (n == 0 || n % 2 != 0) return NAN;
            if(a > b) std::swap(a , b);

            vector<double> x;
            vector<double> y;

            crear_tabla(x, y, a, b, n, str_fn);

            return calcular(x, y);
        }

        static double calcular(vector<double> &x,
                        vector<double> &y){
            size_t n = x.size() - 1;
            if(n <= 0 || n % 2 != 0) return NAN;

            double
            sum_pares = 0.0f,
            sum_impares = 0.0f,
            h = (x[n] - x[0]) / n,
            resultado = 0.0f;

            for(size_t i = 1; i < n; i++){
                if(i % 2 == 0){
                    sum_pares += fabs(y[i]);
                } else {
                    sum_impares += fabs(y[i]);
                }
            }

            resultado = (h / 3.0f) * (fabs(y[0]) + 4.0f * sum_impares + 2.0f * sum_pares + fabs(y[n]));

            return resultado;
        }
    private:
        string str_fn;
    };
}

#endif