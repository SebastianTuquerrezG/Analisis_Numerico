/**
 * @file SimpsonTercio.h
 * @author Sebastian Tuquerrez (jtuquerrez@unicauca.edu.co) - Cristian David Quinayas Rivera (crquinayas@unicauca.edu.co)
 * @brief Libreria para la integracion de funciones  simpson 1/3
 * @version 1.0.0
 * @date 2023-11-24
 *
 * @copyright Copyright (c) 2023
 */
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
        explicit simpson13(string p_fn, string p_dfn, int opcion):str_fn(p_fn), str_dfn(p_dfn), opcion(opcion){}

        /**
         * @brief Calcula la integral de la funcion
         * @param a limite inferior
         * @param b limite superior
         * @param n cantidad de segmentos
         * @return el valor de la integral
         */
        double calcular(double a, double b, int n){
            if (n == 0 || n % 2 != 0) return NAN;
            if(a > b) std::swap(a , b);

            vector<double> x;
            vector<double> y;

            crear_tabla(x, y, a, b, n, str_fn);

            return calcularConError(x, y, str_dfn, opcion);
        }

        /**
         * @brief Calcula la integral de la funcion con error
         * @param x vector de datos independientes x
         * @param y vector de datos dependientes y
         * @param str_dfn texto de la cuarta derivada de la funcion
         * @param opcion tipo de funcion polinomico o no
         * @return el valor de la integral ajustada
         */
        double calcularConError(vector<double> &x,
                        vector<double> &y,
                        const string& str_dfn,
                        int opcion){
            size_t n = x.size() - 1;
            if(n <= 0 || n % 2 != 0) return NAN;

            double
            sum_pares = 0.0f,
            sum_impares = 0.0f,
            h = (x[n] - x[0]) / n,
            resultado;

            for(size_t i = 1; i < n; i++){
                if(i % 2 == 0){
                    sum_pares += fabs(y[i]);
                } else {
                    sum_impares += fabs(y[i]);
                }
            }

            resultado = (h / 3.0f) * (fabs(y[0]) + 4.0f * sum_impares + 2.0f * sum_pares + fabs(y[n]));

            cout << "Resultado Inicial: " << resultado << endl;
            double error, k=0.0f;
            if(opcion == 2){
                error = errorNoPolinomico(x[0], x[n], n, str_dfn);

                cout << "Error no polinomico: " << error << endl;
            } else if(opcion == 1){
                error = errorPolinomico(x[0], x[n], n, str_dfn);

                cout << "Error polinomico: " << error << endl;
            }

            double errorAux = error;
            while (fabs(errorAux) < 1.0f) {
                errorAux *= 10.0f;
                k++;
            }

            double aux = 5* pow(10, -(k+1));
            if (error < aux){
                if(k == 0)
                    cout << "Error: " << error << " con cifras significativas k = " << k << endl;
                else
                    cout << "Error: " << error << " con cifras significativas k = " << k - 1 << endl;
            } else {
                if (k == 0)
                    cout << "Supera al Error: " << aux << ", Error: " << error << " con sifras significativas k = " << k << endl;
                else
                    cout << "Supera al Error: " << aux << ", Error: " << error << " con sifras significativas k = " << k - 1 << endl;
            }

            int segmentosIdeales = calcularSegmentosIdeales(x[0], x[n], str_dfn);
            while (segmentosIdeales % 2 != 0){
                segmentosIdeales++;
            }
            cout << "Segmentos Ideales: " << segmentosIdeales << endl;

            return resultado + error;
        }

        /**
         * @brief Calcula el area de una tabla de datos dada
         * @param x vector de valores independites x
         * @param y vector de valores dependientes y
         * @return el area con los datos de la tabla
         */
        static double calcular(vector<double> &x,
                        vector<double> &y){
            size_t n = x.size() - 1;
            if(n <= 0 || n % 2 != 0) return NAN;

            double
                    sum_pares = 0.0f,
                    sum_impares = 0.0f,
                    h = (x[n] - x[0]) / n,
                    resultado;

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
        string str_fn; /*< Texto de la funcion */
        string str_dfn; /*< Texto de la cuarta derivada de la funcion */
        int opcion; /*< tipo de funcion polinomico o no */

        /**
         * @brief Calcula el error en una funcion no polinomica
         * @param a limite inferior
         * @param b limite superior
         * @param n cantidad de segmentos
         * @param str_dfn cuarta derivada de la funcion
         * @return error no polinomico de la funcion
         */
        double errorNoPolinomico(double a, double b, size_t n, string str_dfn){
            if (n == 0) return NAN;
            if(a > b) std::swap(a , b);

            double max = util::calcularMaximo(str_dfn, a, b);

            double error = -1*(pow((b-a)/n,5) / 90.0f) * max;

            return error;
        }

        /**
         * @brief Calcula el error de la integral en una funcion polinomica
         * @param a limite inferior
         * @param b limite superior
         * @param n cantidad de segmentos
         * @param str_dfn cuarta derivada de la funcion
         * @return error de la integral de la funcion polinomica
         */
        double errorPolinomico(double a, double b, size_t n, string str_dfn) {
            if (n == 0) return NAN;
            if (a > b) std::swap(a, b);

            double puntoMedio = (b + a)/2;
            double p = util::calcularPunto(str_dfn, puntoMedio);
            double h = (b - a) / n;
            double error = -1*(pow(h, 4))*((b - a)/180)*p;

            return error;
        }

        /**
         * @brief Calcula el numero de segmentos ideales para obtener un error menor a 1 * 10^-7
         * @param a limite inferior
         * @param b limite superior
         * @param str_dfn cuarta derivada de la funcion
         * @return
         */
        int calcularSegmentosIdeales(double a, double b, string str_dfn){
            double E = 1 * pow(10, -7);
            double max = util::calcularMaximo(str_dfn, a, b);
            double h = pow(b-a,5);
            double resultado = pow((h/(90*E))*max, 0.2);
            return (int) ceil(resultado);
        }
    };
}

#endif