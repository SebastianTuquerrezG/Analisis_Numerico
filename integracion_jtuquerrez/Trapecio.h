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
            explicit trapecio(string p_fn, string p_dfn):str_fn(p_fn), str_dfn(p_dfn){    }

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

                double k = 0.0f;
                double error = errorNoPolinomico(x[0], x[n], n, str_dfn);
                double errorAux = error;
                for(int i = 0; errorAux > 1.0f; i++){
                    errorAux *= 10.0f;
                    k = i;
                }

                if (error < 5* pow(10, -(k+1))){
                    cout << "Error: " << error
                         << " con sifras significativas k = " << k << endl;
                } else {
                    cout << "Supera al Error: " << error
                         << " con sifras significativas k = " << k << endl;
                }

                return (x[n] - x[0]) * (coef / (2.0f*n)) + error;
            }
    private:
        string str_fn; /*< Evaluador de la funcion */
        string str_dfn; /*< Evaluador de la derivada de la funcion */

        double errorNoPolinomico(double a, double b, size_t n, const string& derivada){
            if (n == 0) return NAN;
            if(a > b) std::swap(a , b);

            double max = util::calcularMaximo(derivada, a, b);

            double error = -1*(pow((b - a), 3) / (12.0f * n * n)) * max;

            return fabs(error);
        }
    };
}

#endif
