#ifndef ROMBERG_H
#define ROMBERG_H

#include <iostream>
#include <string>
#include <vector>

#include "Expression.h"
#include "util.h"
#include "Trapecio.h"

using std::string;
using std::vector;

using integracion::trapecio;
using util::imprimir_tabla;
using util::crear_tabla;

namespace integracion{
    /**
     * @brief Estructura para almacenar el resultado de la integracion de romberg
     */
    struct resultado_romberg{
        double valor; /*!< Valor de la integral */
        double error; /*!< Error de la integral */
    };
    /**
     * @brief Integracion mediante el metodo de Romberg
     */
    class Romberg {
    public:
        Romberg(string p_fn): str_fn(p_fn) {}

        /**
         * @brief Calcula la integral en el intervalo dado
         * @param a limite inferior
         * @param b limite superior
         * @param k numero de aproximaciones
         * @return valor de la integral aproximada
         */
        resultado_romberg calcular(double a, double b, int k){
            resultado_romberg res;
            int i, j, n = 1;

            if(k <= 1) return res;
            if(a > b) std::swap(a , b);

            vector<vector<double>> m(k);
            for(i = 0; i < k; i++){
                m[i].resize(k - i);

                trapecio t(str_fn, 2);

                //Calcular el valor de la primera columna
                m[i][0] = t.calcular(a, b, n);

                n *= 2;
            }

            double pot = 4.0f;
            for(j = 1; j < k; j++){
                for(i = 0; i < k - j; i++){
                    m[i][j] = ((pot/(pot-1))*m[i+1][j-1]) - ((1/(pot-1))*m[i][j-1]);
                }
                pot *= 4.0f;
            }

            res.valor = m[0][k-1];
            res.error = fabs((m[0][k-1] - m[0][k-2])/m[0][k-1]) * 100.0f;

            return res;
        }
    private:
        string str_fn; /*!< Funcion a integrar */
    };
}

#endif
