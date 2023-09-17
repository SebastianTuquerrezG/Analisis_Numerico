#ifndef MULLER_H
#define MULLER_H

/**
 * @file muller.h
 * @author Joan Sebastian Tuquerrez Gomez (jtuquerrez@unicauca.edu.co)
 * @brief libreria que implementa el metodo de muller
 * @version 1.0.0
 * @date 2023-09-15
 *
 * @copyright Copyright (c) 2023
 */

#include <string>
#include <cmath>

#include "Expression.h"
#include "solucion.h"

using std::string;
using raices::solucion;
using raices::calcular_erp;
using raices::es_cero;

namespace raices{
    /**
     * @brief Construye una nueva instancia de muller
     */
    class muller{
    public:
        /**
         * @brief Crea una nueva instancia de Muller
         * @param strFunc Funcion a evaluar
         */
        muller(string strFunc):f(strFunc){
        }

        /**
         * @brief Calcula la raiz de la funcion f utilizando el metodo de muller
         * @param x0 Primera aproximacion
         * @param x1 Segunda aproximacion
         * @param x2 tercera aproximacion
         * @param tol Tolerancia (error relativo porcentual)
         * @param n n numero maximo de iteraciones
         * @return Solucion encontrada. La raiz es NAN si no se encuentra
         */
        solucion calcular(double x0, double x1, double x2, double tol, int n){
            solucion sol;

            double h1 = x1 - x0;
            double h2 = x2 - x1;
            double delta1 = (f(x1) - f(x0)) / h1;
            double delta2 = (f(x2) - f(x1)) / h2;
            double a = (delta2 - delta1) / (h2 + h1);
            int i = 2;

            if (es_cero(f(x0))){
                sol.raiz = x0;
                return sol;
            } else if(es_cero(f(x1))){
                sol.raiz = x1;
                return sol;
            } else if(es_cero(f(x2))){
                sol.raiz = x2;
                return sol;
            }

            while(i <= n){
                double b = delta2 + (h2 * a);
                double D = sqrt(pow(b, 2) - (4 * f(x2) * a));
                double E;

                if (fabs(b - D) < fabs(b + D)){
                    E = b + D;
                } else {
                    E = b - D;
                }

                double h = (-2 * f(x2)) / E;
                double p = x2 + h;

                double erp = calcular_erp(p, x2);
                sol.adicionar({x2, p, erp});

                if(erp < tol){
                    sol.raiz = p;
                    return sol;
                }

                x0 = x1;
                x1 = x2;
                x2 = p;
                h1 = x1 - x0;
                h2 = x2 - x1;
                delta1 = (f(x1) - f(x0)) / h1;
                delta2 = (f(x2) - f(x1)) / h2;
                a = (delta2 - delta1) / (h2 + h1);
                i++;
            }
            return sol;
        }

    private:
        Expression f; /*!< Evaluador de la funcion */
    };
}

#endif
