/**
 * @file Simpson38.h
 * @author Sebastian Tuquerrez (jtuquerrez@unicauca.edu.co) - Cristian David Quinayas Rivera (crquinayas@unicauca.edu.co)
 * @brief Libreria para la integracion de funciones mediante simpson 3/8
 * @version 1.0.0
 * @date 2023-11-24
 *
 * @copyright Copyright (c) 2023
 */
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
        explicit simpson38(string p_fn, string p_dfn):str_fn(p_fn), str_dfn(p_dfn){}

        /**
         * @brief Calcula la integral mediante s38
         * @param a limite inferior
         * @param b limite superior
         * @param n cantidad de segmentos
         * @return valor de la integral
         */
        double calcular(double a, double b, int n){
            //n tiene que ser mayor a 0, impar y multiplo de 3
            if(n == 0 || n % 2 == 0 || n % 3 != 0) return NAN;
            if(a > b) std::swap(a , b);

            vector<double> x;
            vector<double> y;

            crear_tabla(x, y, a, b, n, str_fn);

            return calcular(x, y, str_dfn);
        }

        /**
         * @nrief Calcula la integral mediante s38 con error y la tabla de datos
         * @param x vector independiten de valores x
         * @param y vector dependientes de valores y
         * @param str_dfn texto de la cuarta derivada de la funcion
         * @return Valor de la integral ajustada
         */
        double calcular(vector<double> &x,
                        vector<double> &y,
                        const string& str_dfn) {
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

            int segmentosIdeales = calcularSegmentosIdeales(x[0], x[n], str_dfn);
            while(segmentosIdeales % 3 != 0 && segmentosIdeales %2 == 0){
                segmentosIdeales++;
            }
            cout << "Segmentos Ideales: " << segmentosIdeales << endl;

            return resultado + error;
        }

        /**
         * @brief Calcula el valor de la integral
         * @param x vector independiente de x
         * @param y vector dependiente de y
         * @return valor de la integral con una tabla de datos
         */
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
        string str_fn; /*< Texto de la funcion */
        string str_dfn; /*< Texto de la cuarta derivada de la funcion */

        /**
         * @brief Calcula el error de la integral con una funcion no polinomica
         * @param a limite inferior
         * @param b limite superior
         * @param n cantidad de segmentos
         * @param str_dfn cuarta derivada de la funcion
         * @return error de la integral con funcion no polinomica
         */
        double errorNoPolinomico(double a, double b, int n, const string& str_dfn){
            if (n == 0 || n % 2 == 0 || n % 3 != 0) return NAN;
            if(a > b) std::swap(a , b);

            double max = util::calcularMaximo(str_dfn, a, b);

            double error = -1*((3*pow((b-a)/n,5)) / 80.0f) * max;

            return error;
        }

        /**
         * @brief Calcula los segmentos ideales de la integral para un error menor que 1* 10^-7
         * @param a limite inferior
         * @param b limite superior
         * @param str_dfn cuarta derivada de la funcion
         * @return Cantidad de segmentos ideales para una precision exacta
         */
        int calcularSegmentosIdeales(double a, double b, string str_dfn){
            double E = 1 * pow(10, -7);
            double max = util::calcularMaximo(str_dfn, a, b);
            double h = pow(b-a,5);
            double resultado = pow(3*(h/(80*E))*max, 0.2);
            return (int) ceil(resultado);
        }
    };
}

#endif
