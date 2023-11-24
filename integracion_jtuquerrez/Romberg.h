#ifndef INTEGRACION_JTUQUERREZ_ROMBERG_H
#define INTEGRACION_JTUQUERREZ_ROMBERG_H

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
     * @brief Integracion mediante el metodo de Romberg
     */
    class Romberg {
    public:
        Romberg(string p_fn, string p_dfn): str_fn(p_fn), str_dfn(p_dfn) {}

        /**
         * @brief Calcula la integral en el intervalo dado
         * @param a limite inferior
         * @param b limite superior
         * @param k numero de aproximaciones
         * @return valor de la integral aproximada
         */
        double calcular(double a, double b, int k){
            int i, j, n = 1;

            if(k <= 0) return NAN;
            if(a > b) std::swap(a , b);

            vector<vector<double>> m(k);
            for(i = 0; i < k; i++){
                m[i].resize(k - i);

                trapecio t(str_fn, 2);

                //Calcular el valor de la primera columna
                m[i][0] = t.calcular(a, b, n);

                cout << m[i][0] << endl; //print

                n *= 2;
            }

            double pot = 4.0f;
            for(j = 1; j < k; j++){
                for(i = 0; i < k - j; i++){
                    m[i][j] = ((pot/(pot-1))*m[i+1][j-1]) - ((1/(pot-1))*m[i][j-1]);

                    cout << m[i][j] << endl; //print
                }
                pot *= 4.0f;
            }
            return m[0][k - 1];
        }
    private:
        string str_fn; /*!< Funcion a integrar */
        string str_dfn;
    };
}

#endif
