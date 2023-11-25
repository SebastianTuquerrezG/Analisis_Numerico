#ifndef DERIVACION_H
#define DERIVACION_H

#include <iostream>
#include <string>
#include <vector>

#include "Expression.h"
#include "util.h"

using std::string;
using std::vector;

using util::imprimir_tabla;
using util::crear_tabla;

namespace derivacion {
    /**
     * @brief Derivacion
     */
    class derivada {
    public:
        derivada(string p_fn) : f(p_fn) {}

        /**
         * @brief Calcula la derivada de la funcion
         * @param a limite inferior
         * @param b limite superior
         * @param k numero de aproximaciones
         * @return valor de la derivada
         */
        double primera(double xi, double paso, int diferencias, int direccion) {
            if (diferencias == 1 && direccion == 0){
                double y = f(xi);
                double yip1 = f(xi + paso);

                return (yip1 - y) / paso;
            }

            if (diferencias == 1 && direccion == 1){
                double y = f(xi);
                double yip1 = f(xi + paso);
                double yip2 = f(xi + (2.0f * paso));

                return (yip1 - y) / paso;
            }

            //Primera derivada
            // Una diferencia:
            //  -hacia adelante
            //  -hacia atras
            //  -central
        };

        double segunda(){
            return NAN;
        }

    private:
        Expression f; /*!< Funcion a derivar */
    };
}

#endif