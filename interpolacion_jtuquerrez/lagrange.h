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
    /**
     * @brief Interpolacion mediante el metodo de lagrange
     */
    class lagrange{
    public:
        /**
         * @brief Construye una instancia del metodo de lagrange
         * @param p_x  Variable independiente x
         * @param p_y  Variable dependiente y
         */
        lagrange(vector<double> p_x, vector<double> p_y):x(std::move(p_x)), y(std::move(p_y)){

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
            int n_puntos = grado + 1;
            //TODO: Implementar la interpolacion con un grado menor que n
            //0. Encontrar la poscision de x_int dentro de los datos originales
            //1. Si n_puntos es par: tomar un solo intervalo:
            //  1.1 posInicial = ?? ?? ant ?? n_puntos/2
            //  1.2 posFinal = ?? sig ?? n_puntos/2
            //  1.3 return Interpolar(x_int, posInicial, posFinal)
            //  1.4 retornar el valor interpolado
            //2. Si n_puntos es impar: tomar dos intervalos:
            //  2.0 yint_1 = interpolar(x_int, posInicial, posFinal)
            // 2.1 error_int_1 = cacular_error_int
            //  2.2 yint_2 = interpolar(x_int, posInicial, posFinal)
            //  2.3 error_int_2 = cacular_error_int
            //  2.4 si abs(error_int_1) < abs(error_int_2):
            //    return yint_1            //
            //Validar que el grado no sea mayor a n_puntos
            return NAN;
        }

        /**
         * @brief Construye y evalua el polinomio interpolador de lagrange
         * @param x_int  valor a interpolar
         * @return Valor interpolado
         */
        double interpolar(double x_int, size_t pos_inicial, size_t pos_final){
            double resultado = 0.0f;
            size_t j, k, n = x.size();

            for(j = 0; j < n; j++){
                double lj = 1.0f;
                // calcular la productora en lj

                for(k = 0; k < n; k++){
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
