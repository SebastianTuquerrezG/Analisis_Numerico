/**
 * @file Trapecio.
 * @author Sebastian Tuquerrez (jtuquerrez@unicauca.edu.co) - Cristian David Quinayas Rivera (crquinayas@unicauca.edu.co)
 * @brief Libreria para la integracion de funciones  mediante trapecio
 * @version 1.0.0
 * @date 2023-11-24
 *
 * @copyright Copyright (c) 2023
 */
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
using std::cout;
using std::cin;
using std::endl;

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
             * @param p_dfn Segunda Derivada de la funcion
             */
            explicit trapecio(string p_fn, string p_dfn, int opcion):str_fn(p_fn), str_dfn(p_dfn), opcion(opcion){    }

            explicit trapecio(string p_fn, int opcion):str_fn(p_fn), opcion(opcion){    }

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

                if(opcion == 1)
                    return calcularConError(x, y);
                else
                    return calcular(x, y);
            }

            /**
             * @brief Calcula la integral de una tabla de datos con error
             * @param x valores de la variable independiente
             * @param y valores de la variable dependiente
             * @return valor aproximado de la integral
             */
            double calcularConError(vector<double> &x,
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
                while (fabs(errorAux) < 1.0f) {
                    errorAux *= 10.0f;
                    k++;
                }

                if (error < 5* pow(10, -(k+1))){
                    if(k == 0)
                        cout << "Error: " << error << " con cifras significativas k = " << k << endl;
                    else
                        cout << "Error: " << error << " con cifras significativas k = " << k - 1 << endl;
                } else {
                    if (k == 0)
                        cout << "Supera al Error: " << error << " con sifras significativas k = " << k << endl;
                    else
                        cout << "Supera al Error: " << error << " con sifras significativas k = " << k - 1 << endl;
                }

                return (x[n] - x[0]) * (coef / (2.0f*n)) + error;
            }

            double calcular(vector <double> &x,
                           vector <double> &y){
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
        string str_fn; /*< Texto de la funcion */
        string str_dfn; /*< Texto de la segunda derivada de la funcion */
        int opcion;

        /**
         * @brief Calcula el error no polinomico de trapecio
         * @param a limite inferior
         * @param b limite superior
         * @param n cantidad de segmentos
         * @param derivada segunda derivada
         * @return error no polinomico de la integracion a resolver
         */
        double errorNoPolinomico(double a, double b, size_t n, const string& derivada){
            if (n == 0) return NAN;
            if(a > b) std::swap(a , b);

            double max = util::calcularMaximo(derivada, a, b);
            double h = (b - a) / n;
            double error = -1.0f*(pow(h, 3.0f) / (12.0f)) * max;

            return error;
        }
    };
}

#endif
