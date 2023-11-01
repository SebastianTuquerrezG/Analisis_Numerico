#ifndef REGRESION_H
#define REGRESION_H

#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

#include "util.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::move;
using std::setw;

using util::gauss;

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
                 << " Error Estandar(St): "
                 << st
                 << endl
                 << " Diferencia Cuadratica(Sr): "
                 << sr
                 << endl
                 << " Desviacion Estandar Total(Sy): "
                 << sy
                 << endl
                 << " Error estandar de aproximacion(Syx): "
                 << syx
                 << endl
                 << aceptable
                 << endl
                 << " Coeficiente de determinacion(R2): "
                 << r2 << ", Es aceptable en un: " << r2 * 100 << "%" << endl
                 << endl;
         }
    };

    /**
     * @brief Solucion a una regresion linealiza mediante la funcion potencia
     */
    struct solucion_potencia{
        double c; /*!< Coeficiente de la potencia */
        double a; /*!< Facto del exponente de la potencia */
        solucion_lineal lineal; /*!< Solucion de la regresion lineal */

        /**
        *
        */
        void imprimir(){
            string aceptable = ((lineal.syx < lineal.sy)? " La aproximacion se condidera aceptable ": "La aproximacion no se considera aceptable ");
            cout << " Funcion Potencia: "
                 << "y = " << c << "* x^" << a
                 << endl
                 << " Error Estandar(St): "
                 << lineal.st
                 << endl
                 << " Diferencia Cuadratica(Sr): "
                 << lineal.sr
                 << endl
                 << " Desviacion Estandar Total(Sy): "
                 << lineal.sy
                 << endl
                 << " Error estandar de aproximacion(Syx): "
                 << lineal.syx
                 << endl
                 << aceptable
                 << endl
                 << " Coeficiente de determinacion(R2): "
                 << lineal.r2 << ", Es aceptable en un: " << lineal.r2 * 100 << "%" << endl
                 << endl;
        }
    };

    /**
     * @brief Solucion a una regresion linealiza mediante la funcion exponencial
     */
    struct solucion_exponencial {
        double c; /*!< Coeficiente de la potencia */
        double a; /*!< Facto del exponente de la potencia */
        solucion_lineal lineal; /*!< Solucion de la regresion lineal */

        /**
       *
       */
        void imprimir(){
            string aceptable = ((lineal.syx < lineal.sy)? " La aproximacion se condidera aceptable ": "La aproximacion no se considera aceptable ");
            cout << " Funcion Exponencial: "
                 << "y = " << c << "* e^" << a << "* x"
                 << endl
                 << " Error Estandar(St): "
                 << lineal.st
                 << endl
                 << " Diferencia Cuadratica(Sr): "
                 << lineal.sr
                 << endl
                 << " Desviacion Estandar Total(Sy): "
                 << lineal.sy
                 << endl
                 << " Error estandar de aproximacion(Syx): "
                 << lineal.syx
                 << endl
                 << aceptable
                 << endl
                 << " Coeficiente de determinacion(R2): "
                 << lineal.r2 << ", Es aceptable en un: " << lineal.r2 * 100 << "%"
                 << endl;
        }
    };


    struct solucion_cuadratica{
        double a0; /*!< Termino independiente del polinomio cuadratico */
        double a1; /*!< Coeficiente de x del polinomio */
        double a2; /*!< Coeficiente x^2 del polinomio */
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
            cout << " Polinomio de Regresion: "
                 << "y = " << a2 << "x^2"
                 << ((a1 > 0 )?" + ":" - ") << fabs(a1) << "x"
                 << ((a0 > 0 )? " + ":" - ") << fabs(a0)
                 << endl
                 << " Error Estandar(St): "
                 << st
                 << endl
                 << " Diferencia Cuadratica(Sr): "
                 << sr
                 << endl
                 << " Desviacion Estandar Total(Sy): "
                 << sy
                 << endl
                 << " Error estandar de aproximacion(Syx): "
                 << syx
                 << endl
                 << aceptable
                 << endl
                 << " Coeficiente de determinacion(R2): "
                 << r2 << ", Es aceptable en un: " << r2 * 100 << "%"
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
            string y_label = "",
            string title = "",
            vector<double> opcional = vector<double>()){
        if(x_label.length() == 0 || y_label.length() == 0){
            x_label = "X";
            y_label = "Y";
            title = " ";
        }

        size_t x_width = x_label.length() + 4;
        size_t y_width = y_label.length() + 4;
        size_t title_width = title.length() + 4;
        size_t delineacion = x_width + y_width + title_width + 3;
        cout << setw(title_width)
        << title
        << setw(x_width)
        << x_label
        << setw(y_width)
        << y_label
        << endl
        << str_repeat("=", delineacion)
        << endl;
        for(size_t i = 0; i< X.size(); i++){

            cout << setw(title_width)
            << (opcional.size() > i ? opcional[i] : i+1) // Si opcional no tiene un valor en esta posición, usa 0.0
            << setw(x_width)
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

    /**
     * @brief Regresion linealizada mediante funcion potencia
     */
    class potencia{
    public:
        /**
         * @brief Crea una nueva instancia de regresion mediante funcion potencia
         */
        potencia(vector<double> p_x, vector<double> p_y):x(p_x), y(p_y){
        }

        /**
         * @brief Calcula la regresion linealizada mediante la funcion potencia
         * @return Solucion linealiza
         */
        solucion_potencia calcular() {
            solucion_potencia sol;
            vector<double> X(x);
            vector<double> Y(y);

            //Transformar los datos
            for(unsigned int i = 0; i < X.size(); i++){
                X[i] = log10(X[i]);
                Y[i] = log10(Y[i]);
            }

            //Imprimir los datos
            cout << " Datos transformados: " << endl;
            imprimir_tabla(X, Y, "log10(X)", "log10(Y)");

            //Crear un modelo de regresion lineal con los datos transformados
            lineal_simple ls(X, Y);

            //Calcular la regresion lineal con los datos transformados
            sol.lineal = ls.calcular();

            //Obtener el valor de a
            sol.a = sol.lineal.b1;

            //Obtener el valor de c
            sol.c = pow(10.0f, sol.lineal.b0);

            return sol;
        }

    private:
        vector<double> x; /*!< Variable independiente */
        vector<double> y; /*!< Variable dependiente */
    };

    /**
    * @brief Regresion linealizada mediante funcion potencia
    */
    class exponencial{
    public:
        /**
         * @brief Crea una nueva instancia de regresion mediante funcion exponencial
         */
        exponencial(vector<double> p_x, vector<double> p_y):x(p_x), y(p_y){
        }

        /**
         * @brief Calcula la regresion linealizada mediante la funcion exponencial
         * @return Solucion linealiza
         */
        solucion_exponencial calcular() {
            solucion_exponencial sol;
            vector<double> Y(y);

            //Transformar los datos
            for(unsigned int i = 0; i < Y.size(); i++){
                Y[i] = log(Y[i]);
            }

            //Imprimir los datos
            cout << " Datos transformados: " << endl;
            imprimir_tabla(x, Y, "X", "ln(Y)");

            //Crear un modelo de regresion lineal con los datos transformados
            lineal_simple ls(x, Y);

            //Calcular la regresion lineal con los datos transformados
            sol.lineal = ls.calcular();

            //Obtener el valor de a
            sol.a = sol.lineal.b1;

            //Obtener el valor de c
            sol.c = exp(sol.lineal.b0);

            return sol;
        }

    private:
        vector<double> x; /*!< Variable independiente */
        vector<double> y; /*!< Variable dependiente */
    };

    /**
     * @brief Regresion cuadratica
     */
    class cuadratica {
    public:
        /**
         * @brief Crea una nueva instancia de regresion cuadratica
         * @param p_x Variable independiente
         * @param p_y Variable dependiente
         */
        cuadratica(vector<double> p_x, vector<double> p_y):x(p_x), y(p_y){
        }

        /**
         * @brief Calcula el polinomio de regresion de grado 2
         * @return Polinomio de la solucion
         */
        solucion_cuadratica calcular() {
            solucion_cuadratica sol;
            double sum_x{0}, sum_x2{0}, sum_x3{0}, sum_x4{0};
            double sum_y{0}, sum_xy{0}, sum_x2y{0};
            double y_prom;
            sol.n = x.size();

            if(sol.n <= 3){
                return sol;
            }

            //Imprimir el conjunto de ecuaciones:
            cout << " Conjunto de ecuaciones: " << endl;
            cout << setw(5) << "Xi" << " | " << setw(5) << "Yi" << " | " << setw(7) << "Xi^2" << " | " << setw(12) << "Xi^3" << " | " << setw(12) << "Xi^4" << " | " << setw(9) << "Xi*Yi" << " | " << setw(12) << "Xi^2*Yi" << endl;
            cout << str_repeat("=", 80) << endl;
            for(int i = 0; i < sol.n; i++){
                sum_x += x[i];
                sum_x2 += pow(x[i], 2.0f);
                sum_x3 += pow(x[i], 3.0f);
                sum_x4 += pow(x[i], 4.0f);
                sum_y += y[i];
                sum_xy += x[i] * y[i];
                sum_x2y += pow(x[i], 2.0f) * y[i];
                cout << setw(5) << x[i] << " | " << setw(5) << y[i] << " | " << setw(7) << pow(x[i], 2.0f) << " | " << setw(12) << pow(x[i], 3.0f) << " | " << setw(12) << pow(x[i], 4.0f) << " | " << setw(9) << x[i] * y[i] << " | " << setw(12) << pow(x[i], 2.0f) * y[i] << endl;
            }

            //Imprimir sumatorias
            cout << str_repeat("=", 80) << endl;
            cout << setw(5) << sum_x << " | " << setw(5) << sum_y << " | " << setw(7) << sum_x2 << " | " << setw(12) << sum_x3 << " | " << setw(12) << sum_x4 << " | " << setw(9) << sum_xy << " | " << setw(12) << sum_x2y << endl;
            cout << endl;

            y_prom = sum_y / (double)sol.n;
            sol.st = 0.0f;
            for(size_t i = 0; i < sol.n; i++){
                sol.st += pow(y[i] - y_prom, 2.0f);
            }
            sol.sy = sqrt(sol.st / (double)(sol.n - 1));

            //Crear la matriz de coeficientes
            vector<vector<double>> m{
                    {static_cast<double>(sol.n) , sum_x, sum_x2, sum_y},
                    {sum_x, sum_x2, sum_x3, sum_xy},
                    {sum_x2, sum_x3, sum_x4, sum_x2y},
            };

            //Imprimir la matriz de coeficientes
            cout << " Matriz de ecuaciones lineales simultaneas: " << endl;
            cout << str_repeat("=", 80) << endl;
            for (size_t i = 0; i < m.size(); i++) {
                for (size_t j = 0; j < m[i].size(); j++) {
                    if (j == 0) {
                        cout << "a0*" << setw(12) << m[i][j]; // Imprime "a0" en lugar del primer valor
                    } else if (j == 1) {
                        cout << " + a1*" << setw(12) << m[i][j]; // Imprime "a1" en lugar del segundo valor
                    } else if (j == 2) {
                        cout << " + a2*" << setw(12) << m[i][j]; // Imprime "a2" en lugar del tercer valor
                    } else if (j == m[i].size() - 1) {
                        cout << " = " << setw(12) << m[i][j]; // Imprime "=" antes del último valor
                    } else {
                        cout << setw(12) << m[i][j];
                    }
                }
                cout << endl;
            }
            cout << str_repeat("=", 80) << endl;
            cout << endl;

            //Hallar a0, a1, y a2 mediante eliminacion de gauss
            vector<double> coef = gauss(m);

            sol.a0 = coef[0];
            sol.a1 = coef[1];
            sol.a2 = coef[2];

            //Imprimir los coeficientes
            cout << " Coeficientes del polinomio de regresion: " << endl;
            cout << str_repeat("=", 80) << endl;
            cout << " a0 = " << sol.a0 << endl;
            cout << " a1 = " << sol.a1 << endl;
            cout << " a2 = " << sol.a2 << endl;
            cout << str_repeat("=", 80) << endl;
            cout << endl;

            //Imprimir el polinomio de regresion
            cout << " Polinomio de regresion: " << endl;
            cout << str_repeat("=", 80) << endl;
            cout << " y = " << sol.a0 << " + " << sol.a1 << " * x + " << sol.a2 << " * x^2" << endl;
            cout << str_repeat("=", 80) << endl;
            cout << endl;

            sol.sr = 0.0f;
            for(size_t i = 0; i < sol.n; i++){
                sol.sr += pow(y[i] - sol.a0 - (sol.a1*x[i]) - (sol.a2*pow(x[i], 2.0f)), 2.0f);
            }
            sol.syx = sqrt(sol.sr / (double)(sol.n - 3));

            sol.r2 = (sol.st - sol.sr) / sol.st;

            return sol;
        }
    private:
        vector<double> x; /*!< Variable independiente */
        vector<double> y; /*!< Variable dependiente */
    };
}

#endif