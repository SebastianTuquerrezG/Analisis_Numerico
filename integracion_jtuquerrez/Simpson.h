/**
 * @file Simpson.h
 * @author Sebastian Tuquerrez (jtuquerrez@unicauca.edu.co) - Cristian David Quinayas Rivera (crquinayas@unicauca.edu.co)
 * @brief Libreria para la integracion de tablas de datos median simpson 1/3 y simpson 3/8
 * @version 1.0.0
 * @date 2023-11-24
 *
 * @copyright Copyright (c) 2023
 */
#ifndef SIMPSON_H
#define SIMPSON_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Expression.h"
#include "SimpsonTercio.h"
#include "Simpson38.h"
#include "util.h"

using std::string;
using std::vector;

using util::imprimir_tabla;
using util::crear_tabla;
using integracion::simpson13;
using integracion::simpson38;

namespace integracion{
    /**
     * @brief Integracion mediante los metodos de simpson 1 tercio y simpson 3/8
     */
    class simpson{
        public:
            /**
             * @brief Constructor de la clase
             * @param p_fn Funcion a integrar
             */
            explicit simpson()= default;

            /**
             *  @brief Calcula la integral combinando metodos
             *  @param x Valores independientes x
             *  @param y Valores dependientes y
             *  @return Valor de la integral
             */
            double calcular(vector<double> &x,
                            vector<double> &y) {
                size_t n = x.size() - 1;
                if(n % 2 == 0){
                    return simpson13::calcular(x, y);
                } else if (n % 3 == 0 && n % 2 != 0){
                    return simpson38::calcular(x, y);
                }

                // Calcular el índice de división
                size_t indiceDivision = calcularIndiceDivision(x);

                // Dividir la tabla en dos
                vector<double> x1(x.begin(), x.begin() + indiceDivision);
                vector<double> y1(y.begin(), y.begin() + indiceDivision);

                vector<double> x2(x.begin() + indiceDivision - 1, x.end());
                vector<double> y2(y.begin() + indiceDivision - 1, y.end());

                // Calcular la integral con Simpson (1/3) para la primera tabla
                double resultado1 = simpson13::calcular(x1, y1);

                // Calcular la integral con Simpson (3/8) para la segunda tabla
                double resultado2 = simpson38::calcular(x2, y2);

                // Sumar los resultados de ambas integrales
                return fabs(resultado1) + fabs(resultado2);
            }


    private:
        /**
         * @brief Calcula el índice de división la mitad de la tabla
         * @param x vector de datos
         * @return Indice de división
         */
        size_t calcularIndiceDivision(const vector<double>& x) {
            return x.size() / 2;
        }
    };
}

#endif
