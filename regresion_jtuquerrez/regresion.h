#ifndef REGRESION_H
#define REGRESION_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::move;

namespace regresion{
    /**
     * @brief Solucion mediante Regresion Lineal Simple
     */
    struct solucion_lineal{
        double b0 = NAN; /*!<Termino independiente de la recta */
        double b1 = NAN; /*!< Coeficiente de X */
        double st; /*!< Sumatoria de la diferencia cuadratica entre el valor medido y el promedio */
        double sy; /*!< Desviacion estandar */
        double sr; /*!< Sumatoria de la diferencia cuadratica entre cada y con el y estimado */
        double syx; /*!< Error estandar de aproximacion */
        double r2; /*!< Coeficiente de determinacion */
        size_t n; /*!< Numero de datos */

        /**
         *
         */
         void imprimir(){
             cout << " Recta de regresion: "
                 << "y = " << b1 << "*x "
                 << ((b0 >= 0.0f)? " + " : " - ")
                 << fabs(b0)
                 << endl
                 << " Desviacion estandar: "
                 << sy
                 << endl
                 << " Error estandar de aproximacion: "
                 << syx
                 << endl
                 << " Coeficiente de determinacion: "
                 << r2
                 << endl;
         }
    };

    /**
     * Imprime una tabla de datos
     * @param X  variable independiente
     * @param y variable dependiente
     * @param x_label Etiqueta de la variable independiente
     * @param y_label Etiqueta de la variable dependiente
     */
    void imprimir_tabla(
            vector<double> X,
            vector<double> y,
            string x_label = "X",
            string y_label = "Y"){
        // TODO : Imprimir la tabla
    }

    class lineal_simple{
    public:
        /**
         *
         */
        lineal_simple(vector<double> p_x, vector<double> p_y):x(p_x), y(p_y){
        }

        /**
         * @brief Calcula la recta de regresion lineal
         * @return  Recta de regresion lineal
         */
        solucion_lineal calcular(){
            solucion_lineal sol;

            double sum_xy = 0.0f, sum_x = 0.0f, sum_x2 = 0.0f, sum_y = 0.0f,
                x_prom , y_prom;

            sol.n = x.size();

            for(size_t i = 0; i < sol.n; i++){
                sum_xy += x[i] * y[i];
                sum_x += x[i];
                sum_y += y[i];
                sum_x2 += x[i] * x[i];
            }

            if(sol.n > 0){
                x_prom = sum_x / sol.n;
                y_prom = sum_y / sol.n;

                sol.st = 0.0f;
                for(size_t i = 0; i < sol.n; i++){
                    sol.st += pow(y[i] - y_prom, 2.0f);
                }

                if (sol.n > 1){
                    sol.sy = sqrt(sol.st / (double)(sol.n - 1));
                }
            } else {
                x_prom = NAN;
                y_prom = NAN;
            }

            //Calcular b1 y b0
            sol.b1 = (sum_xy - (y_prom * sum_x)) / (sum_x2 - (x_prom * sum_x));
            sol.b0 = y_prom - (sol.b1 * x_prom);

            sol.sr = 0.0f;
            for(size_t i = 0; i < sol.n; i++){
                sol.sr += pow(y[i] - ((sol.b1 * x[i]) + sol.b0), 2.0f);
            }

            if(sol.n > 2){
                sol.syx = sqrt(sol.sr / (double)(sol.n - 2));
            }

            sol.r2 = (sol.st - sol.sr) / sol.st;
            return sol;
        }

    private:
        vector<double> x; /*!< Variable independiente */
        vector<double> y; /*!< Variable dependiente */
    };
}

#endif