/**
 * @file spline3.h
 * @author Sebastian Tuquerrez (jtuquerrez@unicauca.edu.co) - Cristian David Quinayas Rivera (crquinayas@unicauca.edu.co)
 * @brief Interpolacion mediante trazadores cubicos
 * @version 1.0.0
 * @date 2023-11-03
 *
 * @copyright Copyright (c) 2023
 */

#ifndef SPLINE3_H
#define SPLINE3_H

#include <vector>
#include <utility>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <iostream>

#include "util.h"
#include "newton.h"

using std::vector;
using std::pair;
using std::string;
using std::ostringstream;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::setprecision;
using std::fixed;
using std::defaultfloat;

using util::gauss;
using util::imprimit_matriz;
using util::str_repeat;

namespace interpolacion{
    /**
     * @brief Interpolacion mediante trazadores cubico
     */
    class spline3{
    public:
        /**
         * @brief Construye una nueva instancia del metodo de trazadores cubicos
         * @param p_x Vector de x
         * @param p_y Vector de y
         */
        spline3(vector<double> p_x, vector<double> p_y):x(std::move(p_x)), y(std::move(p_y)){
            //Calcular las segundas derivadas
            f2 = calcular_f2();
        }

        /**
         * @brief Interpola el valor de x_int usando todos los datos
         * @param x_int
         * @return Valor interpolado
         */
        double interpolar(double x_int){
            size_t i = 0;
            double f = 0.0f;

            //Validr si el x_int esta en el intervalo de x
            if(x_int < x[0] || x_int > x[x.size() - 1]){
                cout << "El valor a interpolar no esta en el intervalo de x" << endl;
                return NAN;
            }

            //Determinar el intervalo i en donde se encuentra x_int
            for(i = 0; i < x.size() - 1; i++){
                if(x_int >= x[i] && x_int <= x[i + 1]){
                    i++;
                    break;
                }
            }

            vector<double> coeficientes = calcular_coeficientes(i);

            // Evaluar el polinomio del trazador en x_int
            coeficientes[0] *= pow((x[i]-x_int), 3.0f);
            coeficientes[1] *= pow((x_int-x[i-1]), 3.0f);
            coeficientes[2] *= (x[i] - x_int);
            coeficientes[3] *= (x_int-x[i-1]);

            for(i=0; i<coeficientes.size(); i++) {
                f += coeficientes[i];
            }

            return f;
        }

        /**
        * @brief Calcula e imprime las ecuaciones de los intervalos dentro de un segmento dado
        * @param x_inicial Extremo inferior del segmento
        * @param x_final Extremo superior del segmento
        */
        void interpolar(double x_inicial, double x_final) {
            size_t i;

            //Buscar el iterador donde se encuentran los valores de x_inicial y x_final
            auto i_inicial = find(x.begin(), x.end(), x_inicial);
            auto i_final = find(x.begin(), x.end(), x_final);


            int ini = i_inicial - x.begin() + 1;
            int fin = i_final - x.begin() + 1;

            while(ini < fin) {
                i = ini;

                calcular_coeficientes(i);

                ini++;
            }
        }
    private:
        vector<double> x; /*!< Variable independiente */
        vector<double> y; /*!< Variable dependiente */
        vector<double> f2; /*!< Segundas derivadas */

        /**
		* @brief Calcula e imprime los coeficientes de la ecuacion del intervalo teniendo en cuenta un i dado
		* @param i Posicion del vector de la variable independiente donde se comienzan a calcular los coeficientes del intervalo
		* @return Vector de coeficientes
		*/
        vector<double> calcular_coeficientes(size_t i) {
            vector<double> resultado (4);
            double c1 = (f2[i-1]/(6*(x[i]-x[i-1])));
            double c2 = (f2[i]/(6*(x[i]-x[i-1])));
            double c3 = ((y[i-1]/(x[i]-x[i-1])) - ((f2[i-1]*(x[i]-x[i-1]))/6));
            double c4 = ((y[i]/(x[i]-x[i-1])) - ((f2[i]*(x[i]-x[i-1]))/6));

            //Imprimir la funcion del trazador en el intervalo donde se encuentra x_int
            cout << "Ecuacion del trazador para el intervalo: [" << x[i-1] << ", " << x[i] << "]:" << endl
                 << "f" << i << "(x) =";
            if(c1!=0.0f) {
                cout << ((c1<0)?" - ":"") << fabs(c1) << "*(" << x[i] << "-x)^3";
            }

            if(c2!=0.0f) {
                cout << ((c2<0)?" - ":" + ") << fabs(c2) << "*(x-" << x[i-1] << ")^3";
            }

            cout << ((c3<0)?" - ":" + ") << fabs(c3) << "*(" << x[i] << "-x)";
            cout << ((c4<0)?" - ":" + ") << fabs(c4) << "*(x-" << x[i-1] << ")" << endl;
            cout << endl;

            resultado[0] = c1;
            resultado[1] = c2;
            resultado[2] = c3;
            resultado[3] = c4;

            return resultado;
        }

        /**
		* @brief Calcula las segundas derivadas
		* @return Vector con las segundas derivadas (trazadores)
		*/
        vector<double> calcular_f2() {
            size_t n = x.size();
            size_t intervalos = n - 1;
            size_t i;

            // 1. Construir la matriz de coeficientes m
            // m es una matriz de banda, en donde:
            // En los nodos interiores, se tienen tres valores (coeficientes)
            // En el primer punto se tienen dos coeficientes
            // En el ultimo punto se tienen dos coeficientes
            // m . f2 = c (producto punto)

            vector<vector<double>> m(intervalos - 1);

            for(i=0; i < intervalos - 1; i++) {
                m[i].resize(n);
            }

            for(i=1; i < intervalos; i++) {
                size_t fila = i - 1;
                //Primer coeficiente
                if(i > 1) {
                    m[fila][i-1] = (x[i] - x[i-1]);
                }
                //Segundo coeficiente
                m[fila][i] = 2.0f*(x[i+1] - x[i-1]);
                //Tercer coeficiente
                if(i < intervalos - 1) {
                    m[fila][i+1] = (x[i+1] - x[i]);
                }

                double ci1 = (6 / (x[i+1] - x[i])) * (y[i+1] - y[i]);

                double ci2 = (6 / (x[i] - x[i-1])) * (y[i-1] - y[i]);

                double ci = ci1 + ci2;

                m[fila][intervalos] = ci;
            }

            //Imprimir el sistema de ecuaciones
            cout << "Sistema de ecuaciones: " << endl;
            //Eliminar la primera columna que contiene ceros
            for(i=0; i<m.size(); i++) {
                m[i].erase(m[i].begin());
            }

            for(size_t i = 0; i<m.size(); i++) {
                for(size_t j = 0; j<m[i].size(); j++) {
                    if(j == m[i].size()-1) {
                        cout << setw(4) << "|" << setw(13) << fixed << setprecision(6) << m[i][j] << defaultfloat;
                    }
                    else {
                        cout << setw(6) << m[i][j];
                    }
                }
                cout << endl;
            }

            cout << str_repeat("=", m[0].size()*8) << endl << endl;

            // c = Terminos a la derecha del igual en (18.37)
            // 2. calcular f2 f2 = gauss(m);

            f2 = gauss(m);

            // 2.1 Insertar 0 al inicio y al final de f2
            // 		(f2 en los extremos vale 0)
            f2.insert(f2.begin(), 0.0f);
            f2.insert(f2.end(), 0.0f);

            //Imprimir el vector de resultado
            cout << "Segundas derivadas: " << endl;
            for(i=0; i < f2.size(); i++) {
                cout << "f''(" << x[i] << ") = " << fixed << setprecision(6) << f2[i] << defaultfloat << endl;
            }

            cout << str_repeat("=", 30) << endl << endl;

            //retornar f2
            return f2;
        }
    };
}

#endif
