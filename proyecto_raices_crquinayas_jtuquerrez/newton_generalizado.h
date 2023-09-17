#ifndef NEWTON_GENERALIZADO_H
#define NEWTON_GENERALIZADO_H

/**
 * @file newton_generalido.h
 * @author Joan Sebastian Tuquerrez Gomez (jtuquerrez@unicauca.edu.co)
 * @brief libreria que implementa el metodo de newton generalizado
 * @version 1.0.0
 * @date 2023-09-04
 *
 * @copyright Copyright (c) 2023
 */

#include <string>
#include <iostream>
#include <cmath>

#include "Expression.h"
#include "solucion.h"

using std::string;
using raices::solucion;
using raices::calcular_erp;
using raices::es_cero;

namespace raices{
    /**
    * @brief Implementacion del metodo de Newton generalziado
    */
    class newton_generalizado{
    public:
        /**
        * @brief Construye una nueva instancia de newton generalizado
        * @param strFunc Texto de la funcion
        * @param strdFunc Texto de la funcion primera derivada
        * @param strddFunc Texto de la funcion segunda derivada
        * @param strFunc Texto de la funcion
        */
        newton_generalizado(string strFunc,
                            string strdFunc,
                            string strddFunc):
                f(strFunc),
                df(strdFunc),
                ddf(strddFunc){
        }

        /**
         * @brief Calcula la raiz de la funcion a partir de p0
         * @param p0 Aproximacion inicial
         * @param tol tolerancia (error relativo porcentual)
         * @param n numero maximo de iteraciones
         * @return solucion encontrada. La raiz es NAN si no se encuentra la solucion
         */
        solucion calcular(double p0, double tol, int n ){
            solucion sol;

            int & i = sol.iteraciones = 1;

            while(i < n){
                double p = p0 - ((f(p0)*df(p0))/(pow(df(p0), 2) - (f(p0)*ddf(p0))));

                double erp = calcular_erp(p, p0);

                sol.adicionar({p0, p, erp});

                if(es_cero(f(p))){
                    sol.raiz = p;

                    return sol;
                }

                i++;

                p0 = p;
            }
            return sol;
        }

    private:
        Expression f; /*!< Evaluador de la funcion */
        Expression df; /*!< Evaluador de la derivada de la funcion */
        Expression ddf; /*!< Evaluador de la segunda derivada de la funcion */

    };
};

#endif