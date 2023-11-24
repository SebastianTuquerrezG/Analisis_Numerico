#ifndef SIMPSON38_H
#define SIMPSON38_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Expression.h"
#include "util.h"

using std::string;
using std::vector;

using util::crear_tabla;

namespace integracion{
    /**
     * @brief Integracion mediante el metodo de Simpson 1 tercio
     */
    class simpson38{
    public:
        /**
         * @brief Constructor de la clase
         * @param p_fn Funcion a integrar
         */
        explicit simpson38(string p_fn, string p_dfn):str_fn(p_fn), str_dfn(p_dfn){}

        double calcular(double a, double b, int n){
            //n tiene que ser mayor a 0, impar y multiplo de 3
            if(n == 0 || n % 2 == 0 || n % 3 != 0) return NAN;
            if(a > b) std::swap(a , b);

            vector<double> x;
            vector<double> y;

            crear_tabla(x, y, a, b, n, str_fn);

            return calcular(x, y, str_dfn);
        }

        double calcular(vector<double> &x,
                        vector<double> &y,
                        const string& str_dfn) {
            size_t n = x.size() - 1;
            if(n <= 0 || n % 2 == 0 || n % 3 != 0) return NAN;

            // 1, 4, 7 son numeros
            double sum1 = 0.0f,
                    sum2 = 0.0f,
                    sum3 = 0.0f,
                    h = (x[n] - x[0]) / n,
                    resultado = 0.0f;

            for(size_t i = 1; i < n; i += 3){
                sum1 += fabs(y[i]);
            }

            for (size_t i = 2; i < n; i += 3) {
                sum2 += fabs(y[i]);
            }

            for (size_t i = 3; i < n; i += 3) {
                sum3 += fabs(y[i]);
            }

            resultado = (3.0f * h / 8.0f)  *
                        (fabs(y[0]) +
                         3.0f * sum1 +
                         3.0f * sum2 +
                         2.0f * sum3 +
                         fabs(y[n]));

            double k = 0.0f;
            double error = errorNoPolinomico(x[0], x[n], n, str_dfn);
            double errorAux = error;
            while (errorAux < 1.0f) {
                errorAux *= 10.0f;
                k++;
            }

            if (error < 5* pow(10, -(k+1))){
                cout << "Error: " << error
                     << " con sifras significativas k = " << k - 1 << endl;
            } else {
                cout << "Supera al Error: " << error
                     << " con sifras significativas k = " << k - 1 << endl;
            }

            return resultado + error;
        }

        static double calcular(vector<double> &x,
                        vector<double> &y){
            size_t n = x.size() - 1;
            if(n <= 0 || n % 2 == 0 || n % 3 != 0) return NAN;

            // 1, 4, 7 son numeros
            double sum1 = 0.0f,
                    sum2 = 0.0f,
                    sum3 = 0.0f,
                    h = (x[n] - x[0]) / n,
                    resultado = 0.0f;

            for(size_t i = 1; i < n; i += 3){
                sum1 += fabs(y[i]);
            }

            for (size_t i = 2; i < n; i += 3) {
                sum2 += fabs(y[i]);
            }

            for (size_t i = 3; i < n; i += 3) {
                sum3 += fabs(y[i]);
            }

            resultado = (3.0f * h / 8.0f)  *
                    (fabs(y[0]) +
                    3.0f * sum1 +
                    3.0f * sum2 +
                    2.0f * sum3 +
                    fabs(y[n]));

            return resultado;
        }
    private:
        string str_fn;
        string str_dfn;

        double errorNoPolinomico(double a, double b, int n, const string& str_dfn){
            if (n == 0 || n % 2 == 0 || n % 3 != 0) return NAN;
            if(a > b) std::swap(a , b);

            double max = util::calcularMaximo(str_dfn, a, b);

            double error = -1*((3*pow((b-a)/n,5)) / 80.0f) * max;

            return fabs(error);
        }
    };
}

#endif
