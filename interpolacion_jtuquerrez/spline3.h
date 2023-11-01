#ifndef SPLINE3_H
#define SPLINE3_H

#include <vector>
#include <utility>
#include <cmath>
#include <sstream>
#include <string>
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
         * @brief Construye una nueva isntancia del metodo de trazadores cubicos
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
         * @return
         */
        double interpolar(double x_int){
            size_t i = 0;
            double f;

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

            // Evaluar el polinomio del trazador en x_int
            double c1 = (f2[i-1]/(6*(x[i]-x[i-1])));
            double c2 = (f2[i]/(6*(x[i]-x[i-1])));
            double c3 = ((y[i-1]/(x[i]-x[i-1])) - ((f2[i-1]*(x[i]-x[i-1]))/6));
            double c4 = ((y[i]/(x[i]-x[i-1])) - ((f2[i]*(x[i]-x[i-1]))/6));

            //Imprimir la funcion del trazador en el intervalo donde se encuentra x_int
            cout << "Ecuacion del trazador en donde se encuentra x_int: " << endl << "f" << i << "(x)=";
            if(c1!=0.0f) {
                cout << c1 << "(" << x[i] << "-x)^3" << ((c2<0)?"":"+");
            }

            cout << c2 << "(x-" << x[i-1] << ")^3" << ((c3<0)?"":"+") << c3 << "(" << x[i] << "-x)";

            if(c4!=0.0f) {
                cout << ((c4<0)?"":"+") << c4 << "(x-" << x[i-1] << ")" << endl;
            }else {
                cout << endl;
            }

            c1 *= pow((x[i]-x_int), 3.0f);
            c2 *= pow((x_int-x[i-1]), 3.0f);
            c3 *= (x[i] - x_int);
            c4 *= (x_int-x[i-1]);
            f = c1+c2+c3+c4;

            return f;
        }
    private:
        vector<double> x; /*!< Variable independiente */
        vector<double> y; /*!< Variable dependiente */
        vector<double> f2; /*!< Segundas derivadas */
        /**
         * @brief Calcular las segundas derivadas
         * @return  vector<double> f2 Segundas derivadas
         */
        vector<double> calcular_f2(){
            vector<double> f2;

            size_t n = x.size(), i;
            size_t intervalos = n - 1;
            // 1. Construir la matriz de coeficientes m
            // m es una matriz de banda, en donde:
            // En los puntos interiores, se tienen tres coeficientes
            // En el primer punto se tienen dos coeficientes
            // En el último punto se tienen dos coeficientes
            // m . f2 = c producto punto
            // c = Terminos a la derecha del igual de la ecuacion o los coeficientes que acompañan a las segundas derivadas

            vector<vector<double>> m(intervalos - 1);
            for(i = 0; i < intervalos - 1; i++){
                m[i].resize(n);
            }

            for(i = 1; i < intervalos; i++){
                size_t fila = i - 1;
                //Primer coeficiente
                if (i > 1){
                    //Los puntos interiores tienen f´´(xi -1)
                    m[fila][i - 1] = (x[i] - x[i - 1]);
                }
                //Segundo coeficiente
                m[fila][i] = 2.0f*(x[i + 1] - x[i-1]);
                if(i < intervalos - 1){
                    //Tercer coeficiente
                    //Los puntos interiores tienen f´´(xi + 1)
                    m[fila][i+1] = (x[i + 1] - x[i]);
                }

                //Terminos a la derecha
                double ci1 = (6/(x[i + 1] - x[i]))*(y[i + 1] - y[i]);

                double ci2 = (6/(x[i] - x[i - 1]))*(y[i - 1] - y[i]);

                double ci = ci1 + ci2;

                m[fila][intervalos] = ci;
            }

            //Imprimir el sistema de ecuaciones
            cout << "Sistema de ecuaciones" << endl;
            for(i = 0; i < m.size(); i++){
                m[i].erase(m[i].begin());
            }

            cout << str_repeat("=", m[0].size()*8) << endl;
            for(size_t i = 0; i<m.size(); i++) {
                for(size_t j = 0; j<m[i].size(); j++) {
                    if(j == m[i].size()-1) {
                        cout << setw(4) << "|" << setw(13) << setprecision(6) << m[i][j];
                    }
                    else {
                        cout << setw(6) << m[i][j];
                    }
                }
                cout << endl;
            }
            cout << str_repeat("=", m[0].size()*8) << endl;

            // 2. Calcular f2, f2 = gauss

            f2 = gauss(m);

            // 2.1 Inservar 0 al inicio y al final de f2
            //  (f2 en los extremos vale 0)
            f2.insert(f2.begin(), 0);
            f2.insert(f2.end(), 0);

            cout << "Segundas derivadas" << endl;
            cout << str_repeat("=", 30) << endl << endl;
            for(i = 0; i<f2.size(); i++) {
                cout << "f''(" << x[i] << ") = " << f2[i] << endl;
            }
            cout << str_repeat("=", 30) << endl << endl;
            cout << endl;

            return f2;
        }
    };
}

#endif
