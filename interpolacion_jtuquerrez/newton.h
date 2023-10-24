/**
 * @file newton.h
 * @brief Interpolacion mediante el metodo de diferencias divididas de Newton
 */

#ifndef NEWTON_H
#define NEWTON_H

#include <utility>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>

using std::vector;
using std::string;
using std::ostringstream;
using std::cout;
using std::cin;
using std::endl;

namespace  interpolacion{
    class newton{
    public:
        /**
         * @brief Crea una instancia de Newton
         * @param p_x  Variable independiente
         * @param p_y  Variable dependiente
         */
        newton(vector<double> p_x, vector<double> p_y):x(std::move(p_x)), y(std::move(p_y)){
            calcular_coeficientes();
        };

        /**
         * @brief Construye y retorna el polinomio
         * @return
         */
        string polinomio(){
            ostringstream oss;

            oss << b[0];

            for (size_t i = 1; i < b.size(); i++){
                oss << ((b[i] < 0) ? " - " : " + ")
                    << fabs(b[i]) << " ";
                for (size_t j = 0; j < i; j++) {
                    oss << "(x - " << x[j] << ")";
                }
            }

            return oss.str();
        }

        /**
         * @brief Calcula el valor de y interpolado
         * @param x_int Valor de x a interpolar
         * @return Valor de y interpolado
         */
        double interpolar(double x_int){
            if (b.empty()){
                return NAN;
            }

            ostringstream oss;
            double f = b[0];

            for (size_t i = 1; i < b.size(); i++){
                double prod = 1;
                for (size_t j = 0; j < i; j++) {
                    prod *= (x_int - x[j]);
                }

                f += prod * b[i];
            }

            return f;
        }
    private:
        /**
         * @brief Calcula los coeficientes b0, b1, b2, ... del polinomio
         */
        void calcular_coeficientes(){
            size_t i, j;
            size_t n = x.size();
            vector<vector<double>> f(n);

            for (i = 0; i < n; i++){
                f[i].resize(n - i);
            }

            //Llenar la primera columna
            for (i = 0; i < n; i++){
                f[i][0] = y[i];
            }

            //Calcular los coeficientes
            for (j = 1; j < n; j++){
                for (i = 0; i < n - j; i++){
                    f[i][j] = (f[i + 1][j - 1] - f[i][j - 1]) / (x[i + j] - x[i]);
                }
            }

            //Tomar el vector de coeficientes de la primera fila de la matriz
            b = f[0];
        }
        vector<double> x; /*!<Variable independiente> */
        vector<double> y; /*!<Variable dependiente>*/
        vector<double> b; /*!<Vector de coeficientes>*/
    };
}

#endif