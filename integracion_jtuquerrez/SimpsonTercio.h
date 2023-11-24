#ifndef SIMSONTERCIO_H
#define SIMSONTERCIO_H

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
    class simpson13{
    public:
        /**
         * @brief Constructor de la clase
         * @param p_fn Funcion a integrar
         */
        explicit simpson13(string p_fn, string p_dfn, int opcion):str_fn(p_fn), str_dfn(p_dfn), opcion(opcion){}

        double calcular(double a, double b, int n){
            if (n == 0 || n % 2 != 0) return NAN;
            if(a > b) std::swap(a , b);

            vector<double> x;
            vector<double> y;

            crear_tabla(x, y, a, b, n, str_fn);

            return calcularConError(x, y, str_dfn, opcion);
        }

        double calcularConError(vector<double> &x,
                        vector<double> &y,
                        const string& str_dfn,
                        int opcion){
            size_t n = x.size() - 1;
            if(n <= 0 || n % 2 != 0) return NAN;

            double
            sum_pares = 0.0f,
            sum_impares = 0.0f,
            h = (x[n] - x[0]) / n,
            resultado;

            for(size_t i = 1; i < n; i++){
                if(i % 2 == 0){
                    sum_pares += fabs(y[i]);
                } else {
                    sum_impares += fabs(y[i]);
                }
            }

            resultado = (h / 3.0f) * (fabs(y[0]) + 4.0f * sum_impares + 2.0f * sum_pares + fabs(y[n]));
            double error;
            if(opcion == 2){
                double k = 0.0f;
                error = errorNoPolinomico(x[0], x[n], n, str_dfn);
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
            } else if(opcion == 1){
                error = errorPolinomico(x[0], x[n], n, str_dfn);

                cout << "Error polinomico: " << error << endl;
            }

            int segmentosIdeales = calcularSegmentosIdeales(x[0], x[n], str_dfn);
            while (segmentosIdeales % 2 != 0){
                segmentosIdeales++;
            }
            cout << "Segmentos Ideales: " << segmentosIdeales << endl;

            return resultado + error;
        }

        static double calcular(vector<double> &x,
                        vector<double> &y){
            size_t n = x.size() - 1;
            if(n <= 0 || n % 2 != 0) return NAN;

            double
                    sum_pares = 0.0f,
                    sum_impares = 0.0f,
                    h = (x[n] - x[0]) / n,
                    resultado;

            for(size_t i = 1; i < n; i++){
                if(i % 2 == 0){
                    sum_pares += fabs(y[i]);
                } else {
                    sum_impares += fabs(y[i]);
                }
            }

            resultado = (h / 3.0f) * (fabs(y[0]) + 4.0f * sum_impares + 2.0f * sum_pares + fabs(y[n]));

            return resultado;
        }
    private:
        string str_fn;
        string str_dfn;
        int opcion;

        double errorNoPolinomico(double a, double b, size_t n, string str_dfn){
            if (n == 0) return NAN;
            if(a > b) std::swap(a , b);

            double max = util::calcularMaximo(str_dfn, a, b);

            double error = -1*(pow((b-a)/n,5) / 90.0f) * max;

            return error;
        }

        double errorPolinomico(double a, double b, size_t n, string str_dfn) {
            if (n == 0) return NAN;
            if (a > b) std::swap(a, b);

            double puntoMedio = (b + a)/2;
            double p = util::calcularPunto(str_dfn, puntoMedio);
            double h = (b - a) / n;
            double error = -1*(pow(h, 4))*((b - a)/180)*p;

            return error;
        }

        int calcularSegmentosIdeales(double a, double b, string str_dfn){
            double E = 1 * pow(10, -7);
            double max = util::calcularMaximo(str_dfn, a, b);
            double h = pow(b-a,5);
            double resultado = pow((h/(90*E))*max, 0.2);
            return (int) ceil(resultado);
        }
    };
}

#endif