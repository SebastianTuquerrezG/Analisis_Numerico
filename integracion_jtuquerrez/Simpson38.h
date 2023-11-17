#ifndef SIMPSON38_H
#define SIMPSON38_H

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
    class simpson38{
    public:
        /**
         * @brief Constructor de la clase
         * @param p_fn Funcion a integrar
         */
        explicit simpson38(string p_fn):str_fn(p_fn){}

        double calcular(double a, double b, int n){
            //n tiene que ser mayor a 0, impar y multiplo de 3
            if(n == 0 || n % 2 == 0 || n % 3 != 0) return NAN;
            if(a > b) std::swap(a , b);

            vector<double> x;
            vector<double> y;

            crear_tabla(x, y, a, b, n, str_fn);

            return calcular(x, y);
        }

        static double calcular(vector<double> &x,
                        vector<double> &y){
            size_t n = x.size() - 1;
            if(n <= 0 || n % 2 == 0 || n % 3 != 0) return NAN;

            // 1, 4, 7 son numeros
            double sum1 = 0.0f,
                    sum2 = 0.0f,
                    sum3 = 0.0f,
                    h = (x[n] - x[0]) / n,
                    resultado = 0.0f;

            for(size_t i = 1; i < n; i += 3){
                sum1 += fabs(y[i]);
            }

            for (size_t i = 2; i < n; i += 3) {
                sum2 += fabs(y[i]);
            }

            for (size_t i = 3; i < n; i += 3) {
                sum3 += fabs(y[i]);
            }

            resultado = (3.0f * h / 8.0f)  *
                    (fabs(y[0]) +
                    3.0f * sum1 +
                    3.0f * sum2 +
                    2.0f * sum3 +
                    fabs(y[n]));

            return resultado;
        }
    private:
        string str_fn;
    };
}

#endif
