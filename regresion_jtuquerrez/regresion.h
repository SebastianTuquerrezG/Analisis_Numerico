#ifndef REGRESION_H
#define REGRESION_H

#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::move;
using std::setw;

namespace regresion{

    /**
     * @brief Repite una cadena de caracteres
     * @param s Cadena a repetir
     * @param n Cantidad de repeticiones
     * @return Concatenacion de s n veces
     */
    string str_repeat(const string& s, int n){
        string ret;
        for(int i = 0; i < n; i++){
            ret += s;
        }

        return ret;
    }
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
             string aceptable = ((syx < sy)? " La aproximacion se condidera aceptable ": "La aproximacion no se considera aceptable ");
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
                 << aceptable
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
            vector<double> Y,
            string x_label = "",
            string y_label = ""){
        if(x_label.length() == 0 || y_label.length() == 0){
            x_label = "X";
            y_label = "Y";
        }

        size_t x_width = x_label.length() + 4;
        size_t y_width = y_label.length() + 4;
        size_t delineacion = x_width + y_width + 2;
        cout << setw(x_width)
        << x_label
        << setw(y_width)
        << y_label
        << endl
        << str_repeat("=", delineacion)
        << endl;
        for(size_t i = 0; i< X.size(); i++){
            cout << setw(x_width)
            << X[i]
            << setw(y_width)
            << Y[i]
            <<endl;
        }
        cout << str_repeat("=", delineacion) << endl;
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