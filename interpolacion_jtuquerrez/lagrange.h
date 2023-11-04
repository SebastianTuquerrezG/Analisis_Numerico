/**
 * @file lagrange.h
 * @author Sebastian Tuquerrez (jtuquerrez@unicauca.edu.co) - Cristian David Quinayas Rivera (crquinayas@unicauca.edu.co)
 * @brief Interpolacion mediante lagrange
 * @version 1.0.0
 * @date 2023-11-03
 *
 * @copyright Copyright (c) 2023
 */

#ifndef LAGRANGE_H
#define LAGRANGE_H

#include <utility>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>

#include "newton.h"

using std::vector;
using std::string;
using std::ostringstream;
using std::cout;
using std::cin;
using std::endl;

using interpolacion::newton;

namespace interpolacion{
    /**
     * @brief Interpolacion mediante lagrange
     */
    class lagrange{
    public:
        /**
         * @brief Construye una instancia del metodo de lagrange
         * @param p_x  Variable independiente x
         * @param p_y  Variable dependiente y
         */
        lagrange(vector<double> p_x, vector<double> p_y):x(std::move(p_x)), y(std::move(p_y)){

        };

        /**
         * @brief Calcula el error de interpolacion
         * @param x_int  valor a interpolar
         * @param pos_inicial  posicion inicial del intervalo
         * @param pos_final  posicion final del intervalo
         * @return Error de interpolacion
         */
        double cacular_error_int(double x_int, int grado){
            double valor_interpolado = interpolar(x_int, grado);

            // Encontrar el índice más cercano a x_int en el vector de las x
            int indice_cercano = 0;
            double distancia_minima = std::abs(x[0] - x_int);

            for (int i = 1; i < x.size(); ++i) {
                double distancia_actual = std::abs(x[i] - x_int);
                if (distancia_actual < distancia_minima) {
                    distancia_minima = distancia_actual;
                    indice_cercano = i;
                }
            }

            double valor_real = y[indice_cercano];

            return std::abs(valor_interpolado - valor_real);
        }

        /**
         * @brief Imprime el polinomio de lagrange
         * @return Polinomio de lagrange
         */
        string polinomio() {
            ostringstream oss;

            int n = x.size();

            for (int i = 0; i < n; ++i) {
                oss << y[i];
                for (int j = 0; j < n; ++j) {
                    if (i != j) {
                        oss << "*(x - " << x[j] << ")/(" << x[i] << " - " << x[j] << ")";
                    }
                }
                if (i != n - 1) {
                    oss << " + ";
                }
            }

            return oss.str();
        }

        /**
         * @brief Interpola el valor de x_int usando todos los datos
         * @param x_int  valor a interpolar
         * @return Valor interpolado
         */
        double interpolar(double x_int){
            return interpolar (x_int, 0, x.size() - 1);
        }

        /**
         * @brief Intepolar el valor de x_int usando un polinomio del grado especificado
         * @param x_int Valor a interpolar sobre el cual se calcula el polinomio p(x)
         * @param grado Grado del polinomio
         * @return Valor interpolado
         */
        double interpolar(double x_int, int grado){
            //Validar que x_int este dentro del rango de x
            if (x_int < x[0] || x_int >= x[x.size() - 1]){
                return NAN;
            }

            int n_puntos = grado + 1,
                n = x.size(),
                pos_ant = 0,
                pos_sig = x.size() - 1,
                pos_inicial = 0,
                pos_final = n - 1,
                pos_inicial_aux,
                pos_final_aux;
            //Validar que el grado no sea mayor a n_puntos
            if (grado < 0 || grado >= n_puntos){
                throw std::invalid_argument("Grado invalido");
            }

            //Encontrar la posicion anterior y siguiente de x_int dentro de los datos originales
            for (int i = 0; i < x.size(); i++) {
                if (x[i] <= x_int) {
                    pos_ant = i;
                } else if (x[i] > x_int) {
                    pos_sig = i;
                    break;
                }
            }

            pos_inicial = pos_ant - n_puntos / 2;
            pos_final = pos_sig + n_puntos / 2;
            //Si n_puntos es par
            if (n_puntos % 2 == 0) {
                return interpolar(x_int, pos_inicial, pos_final);
            } else { //si n_puntos es impar
                pos_inicial_aux = pos_inicial + 1;
                pos_final_aux = pos_final - 1;

                //Validar posiciones
                if (pos_inicial_aux >= pos_final_aux || pos_final_aux >= n || pos_inicial_aux >= n || pos_inicial < 0 || pos_final >= n) {
                    return interpolar(x_int, pos_inicial, pos_final);
                }

                double y_int_1 = interpolar(x_int, pos_inicial, pos_final);
                double y_int_2 = interpolar(x_int, pos_inicial_aux, pos_final_aux);

                if (std::isnan(y_int_1)) {
                    return y_int_2;
                } else if(std::isnan(y_int_2)) {
                    return y_int_1;
                }

                // y_int_1 y y_int_2 son diferente de nan
                //Sacar los datos de x en el intervalo pos_inicial_aux, pos_final_aux con el dato adicional
                // con un for del x grande (pos_inicial) sacr los datos a x1 (0), x1 es un subvector de x que tiene desde x[pos_inicial_aux] hasta x[pos_final_aux]
                vector<double> x1 (x.begin() + pos_inicial, x.begin() + pos_final);

                //Sacar los datos de y en el intervalo pos_inicial_aux, pos_final_aux con el dato adicional
                vector<double> y1 (y.begin() + pos_inicial, y.begin() + pos_final);

                vector<double> F1 = newton::calcular_coeficientes(x1, y1);

                //Calcular el error
                double prod_1 = 1.0f; //Ultimo coeficiente de F1

                //Quitar el dato adicional del fin
                F1.erase(F1.end());

                //Calcular la productoria de R * (x_int - x1[0]) * (x_int - x1[1]) * ... * (x_int - x1[n_puntos - 1]) sin tener en cuenta el dato adicional
                for (int i = 0; i < F1.size(); i++) {
                    prod_1 *= (x_int - x1[i]);
                }
                double error_int_1 =  F1[F1.size() - 1] * prod_1 ;

                vector<double> x2 (x.begin() + pos_inicial_aux, x.begin() + pos_final_aux);

                //Sacar los datos de y en el intervalo pos_inicial_aux, pos_final_aux con el dato adicional
                vector<double> y2 (y.begin() + pos_inicial_aux, y.begin() + pos_final_aux);

                vector<double> F2 = newton::calcular_coeficientes(x2, y2);

                //Calcular el error
                double prod_2 = 1.0f; //Ultimo coeficiente de F1

                //Quitar el dato adicional del inicio
                F2.erase(F2.begin());

                //Calcular la productoria de R * (x_int - x1[0]) * (x_int - x1[1]) * ... * (x_int - x1[n_puntos - 1]) sin tener en cuenta el dato adicional
                for (int i = 0; i < F2.size(); i++) {
                    prod_2 *= (x_int - x1[i]);
                }
                double error_int_2 =  F2[F2.size() - 1] * prod_2;

                if (std::fabs(error_int_1) < std::fabs(error_int_2)) {
                    return y_int_1;
                } else {
                    return y_int_2;
                }
            }
        }

        /**
         * @brief Construye y evalua el polinomio interpolador de lagrange
         * @param x_int  valor a interpolar
         * @param pos_inicial  posicion inicial del intervalo
         * @param pos_final  posicion final del intervalo
         * @return Valor interpolado
         */
        double interpolar(double x_int, int pos_inicial, int pos_final){
            double resultado = 0.0f;
            int j, k, n = x.size();

            if (pos_inicial < 0 || pos_inicial >= pos_final || pos_final >= n || pos_inicial >= n || x_int < x[pos_inicial] || x_int > x[pos_final])
                throw std::invalid_argument("Posicion inicial o final invalida");

            if(x_int == x[pos_inicial]){
                return y[pos_inicial];
            }

            if(x_int == x[pos_final]){
                return y[pos_final];
            }

            for(j = pos_inicial; j < pos_final; j++){
                double lj = 1.0f;
                // calcular la productora en lj

                for(k = pos_inicial; k < pos_final; k++){
                    if(j != k){
                        lj *= (x_int - x[k]) / (x[j] - x[k]);
                    }
                }
                resultado += y[j] * lj;
            }
            return resultado;
        }
    private:
        vector<double> x; /*!< Variable independiente x */
        vector<double> y; /*!< Variable dependiente y */
    };
}

#endif
