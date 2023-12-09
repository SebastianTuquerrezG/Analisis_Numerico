#ifndef DERIVACION_H
#define DERIVACION_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Expression.h"
#include "util.h"

using std::string;
using std::vector;

using util::imprimir_tabla;

namespace derivacion {
    /**
     * @brief Derivacion
     */
    class derivada {
    public:
        /**
         * @brief Derivacion
         */
        derivada(string p_fn) : f(p_fn) {
        }

        /**
         * @brief Calcula la derivada de la funcion
         * @param xi
         * @param paso
         * @param diferencias
         * @param direccion
         * @return valor de la derivada
         */
        double primeraDerivada(double xi, double paso, int diferencias, int direccion) {
            //Comprobar que la cantidad de diferencias sea o 1 o 2.
            if((diferencias != 1) && (diferencias != 2)) {
                return NAN;
            }
            //Comprobar que la direccion sea una de las 3 posibles (atras, adelante o central)
            if((direccion != atras) && (direccion != central) && (direccion != adelante)) {
                return NAN;
            }

            double y = f(xi);
            double yip1 = f(xi + paso);
            double yip2 = f(xi + (2.0f * paso));
            double yim1 = f(xi - paso);
            double yim2 = f(xi - (2.0f * paso));

            switch(diferencias) {
                //Primeras diferencias
                case 1:
                    if (direccion == adelante){
                        vector<double> xVec = {xi, (xi+paso)};
                        vector<double> yVec = {y, yip1};
                        imprimir_tabla(xVec, yVec, "X", "Y", "Tabla:");
                        return (yip1 - y) / paso;
                    }
                    else if(direccion == atras) {
                        vector<double> xVec = {(xi+paso), xi};
                        vector<double> yVec = {yip1, y};
                        imprimir_tabla(xVec, yVec, "X", "Y", "Tabla:");
                        return (y - yim1) / paso;
                    }
                    else {
                        vector<double> xVec = {(xi-paso), xi, (xi+paso)};
                        vector<double> yVec = {yim1, y, yip1};
                        imprimir_tabla(xVec, yVec, "X", "Y", "Tabla:");
                        return (yip1 - yim1) / (2.0f * paso);
                    }

                //Segundas diferencias
                case 2:
                    if (direccion == adelante) {
                        vector<double> xVec = {xi, (xi+paso), (xi+(2.0f*paso))};
                        vector<double> yVec = {y, yip1, yip2};
                        imprimir_tabla(xVec, yVec, "X", "Y", "Tabla:");
                        return ((-1.0f * yip2) + (4.0f * yip1) - (3.0f * y)) / (2.0f * paso);
                    }
                    else if(direccion == atras) {
                        vector<double> xVec = {(xi-(2.0f*paso)), (xi-paso), xi};
                        vector<double> yVec = {yim2, yim1, y};
                        imprimir_tabla(xVec, yVec, "X", "Y", "Tabla:");
                        return ((3.0f * y) - (4.0f * yim1) + yim2) / (2.0f * paso);
                    }
                    else {
                        vector<double> xVec = {(xi-(2.0f*paso)), (xi-paso), xi, (xi+paso), (xi+(2.0f*paso))};
                        vector<double> yVec = {yim2, yim1, y, yip1, yip2};
                        imprimir_tabla(xVec, yVec, "X", "Y", "Tabla:");
                        return ((-1.0f * yip2) + (8.0f * yip1) - (8.0f * yim1) + yim2) / (12.0f * paso);
                    }
            }
            return NAN;
        };

        /**
         * @brief Calcula la segunda derivada de la funcion
         * @param xi
         * @param paso
         * @param diferencias
         * @param direccion
         * @return valor de la segunda derivada
         */
        double segundaDerivada(double xi, double paso, int diferencias, int direccion){
            //Comprobar que la cantidad de diferencias sea o 1 o 2.
            if((diferencias != 1) && (diferencias != 2)) {
                return NAN;
            }
            //Comprobar que la direccion sea una de las 3 posibles (atras, adelante o central)
            if((direccion != atras) && (direccion != central) && (direccion != adelante)) {
                return NAN;
            }

            double y = f(xi);
            double yip1 = f(xi + paso);
            double yip2 = f(xi + (2.0f * paso));
            double yip3 = f(xi + (3.0f * paso));
            double yim1 = f(xi - paso);
            double yim2 = f(xi - (2.0f * paso));
            double yim3 = f(xi - (3.0f * paso));

            switch(diferencias) {
                //Primeras diferencias
                case 1:
                    if (direccion == adelante){
                        return (yip2 - (2.0f * yip1) + y) / pow(paso, 2.0f);
                    }
                    else if(direccion == atras) {
                        return (y - (2.0f * yim1) + yim2) / pow(paso, 2.0f);
                    }
                    else {
                        return (yip1 - (2.0f * y) + yim1) / pow(paso, 2.0f);
                    }

                //Segundas diferencias
                case 2:
                    if (direccion == adelante) {
                        return ((-1.0f * yip3) + (4.0f * yip2) - (5.0f * yip1) + (2.0f * y)) / (2.0f * paso);
                    }
                    else if(direccion == atras) {
                        return ((2.0f * y) - (5.0f * yim1) + (4.0f * yim2) - yim3) / (2.0f * paso);
                    }
                    else {
                        return ((-1.0f * yip2) + (16.0f * yip1) - (30.0f * y) + (17.0f * yim1) - yim2) / (12.0f * (2.0f * paso));
                    }
            }
            return NAN;
        }

        double calcularError(double va, double vm){
            return fabs((va-vm)/va)*100;
        }

    private:
        Expression f; /*!< Función a derivar. */
        const int adelante = 0; /*!< Dirección de la derivada hacia adelante. */
        const int atras = 1; /*!< Dirección de la derivada hacia atrás. */
        const int central = 2; /*!< Dirección de la derivada central. */
    };
}

#endif