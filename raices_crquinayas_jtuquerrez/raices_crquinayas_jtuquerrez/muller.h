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

#include "Expression.h"
#include "solucion.h"

using std::string;
using raices::solucion;
using raices::calcular_erp;
using raices::es_cero;

namespace raices{
    /**
     * @brief Construye una nueva instancia de muller
     * @param strFunc Texto de la funcion
     */
    class muller{
    public:
        muller(string strFunc):f(strFunc){

        }

        solucion calcular()
    };
}

#endif //RAICES_CRQUINAYAS_JTUQUERREZ_MULLER_H
