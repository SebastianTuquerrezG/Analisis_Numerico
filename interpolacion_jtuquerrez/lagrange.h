/**
 * @file lagrange.h
 * @brief Interpolacion mediante el metodo de lagrange
 * @author Sebastian Tuquerrez jtuquerrez@unicauca.edu.co
 */

#ifndef LAGRANGE_H
#define LAGRANGE_H

#include <utility>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::ostringstream;
using std::cout;
using std::cin;
using std::endl;

namespace interpolacion{
    class lagrange{
    public:
        /**
         * @brief Construye una instancia del metodo de lagrange
         * @param p_x  Variable independiente x
         * @param p_y  Variable dependiente y
         */
        lagrange(vector<double> p_x, vector<double> p_y):x(std::move(p_x)), y(std::move(p_y)){

        };

        //TODO: Error de interpolacion
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
            return interpolar (x_int, 0, x.size() );
        }

        /**
         * @brief Intepolar el valor de x_int usando un polinomio del grado especificado
         * @param x_int Valor a interpolar sobre el cual se calcula el polinomio p(x)
         * @param grado Grado del polinomio
         * @return Valor interpolado
         */
        double interpolar(double x_int, int grado){
            int n_puntos = grado + 1, n = x.size(), pos_inicial = 0, pos_final = n - 1;
            //TODO: Validar que el grado no sea mayor a n_puntos
            if (grado < 0 || grado >= n_puntos){
                throw std::invalid_argument("Grado invalido");
            }
            //TODO: Implementar la interpolacion con un grado menor que n
            // 0. Encontrar la poscision anterior y siguiente de x_int dentro de los datos originales
            // 1. Si n_puntos es par: tomar un solo intervalo:
            //  1.1 posInicial = formula para saber cuantos puntos tomar por abajo de x_int y cuantos por encima, ?? anterior ?? n_puntos/2
            //  1.2 posFinal = formula para saber cuantos puntos tomar por abajo de x_int y cuantos por encima,?? siguiente ?? n_puntos/2
            //  1.3 return Interpolar(x_int, posInicial, posFinal)
            //  1.4 retornar el valor interpolado
            // 2. Si n_puntos es impar: tomar dos intervalos:
            //  2.0 yinterpolado_1 = interpolar(x_int, posInicial que se debe calcular, posFinal que se debe calcular )
            //  2.1 error_int_1 = crear rutina que calcula el error de interpolacion llamadaa cacular_error_int(parametros a definir)
            //  2.2 yinterpolado_2 = interpolar(x_int, posInicial que se debe calcular, posFinal que se debe calcular)
            //  2.3 error_int_2 = con cacular_error_int(parametros a definir)
            //  2.4 si abs(error_int_1) < abs(error_int_2):
            //    return yinterpolado_1
            //  2.5 sino return yinterpolado_2

            for (int i = 0; i < n - 1; ++i) {
                if (x[i] <= x_int && x_int <= x[i + 1]) {
                    pos_inicial = i;
                    pos_final = i + 1;
                    break;
                }
            }

            if (n_puntos % 2 == 0) {
                return interpolar(x_int, pos_inicial, pos_final);
            } else {
                double y1 = interpolar(x_int, pos_inicial, pos_final);
                double error1 = cacular_error_int(x_int, grado);

                double y2, error2;

                if(pos_inicial > 0){
                    y2 = interpolar(x_int, pos_inicial - 1, pos_final);
                    error2 = cacular_error_int(x_int, grado);
                    if (std::abs(error1) < std::abs(error2)) {
                        return y1;
                    } else {
                        return y2;
                    }
                } else {
                    return y1;
                }
            }
        }

        /**
         * @brief Construye y evalua el polinomio interpolador de lagrange
         * @param x_int  valor a interpolar
         * @return Valor interpolado
         */
        double interpolar(double x_int, int pos_inicial, int pos_final){
            double resultado = 0.0f;
            int j, k, n = x.size();

            if (pos_inicial >= pos_final || pos_final >= n || pos_inicial >= n)
                throw std::invalid_argument("Posicion inicial o final invalida");

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
