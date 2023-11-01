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
            //Calcular los coeficientes con x e y
            b = calcular_coeficientes(x, y);
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
            return interpolar(x_int, 0, x.size() - 1);
        }

        /**
        * @brief Intepolar el valor de x_int usando un polinomio del grado especificado
        * @param x_int Valor a interpolar sobre el cual se calcula el polinomio p(x)
        * @param grado Grado del polinomio
        * @return Valor interpolado
        */
        double interpolar(double x_int, int grado){
            //Validar que x_int este dentro del rango de x
            if (x_int < x[0] || x_int >= x[x.size() - 1]){
                return NAN;
            }

            int n_puntos = grado + 1,
                    n = x.size(),
                    pos_ant = 0,
                    pos_sig = x.size() - 1,
                    pos_inicial = 0,
                    pos_final = n - 1,
                    pos_inicial_aux,
                    pos_final_aux;
            //Validar que el grado no sea mayor a n_puntos
            if (grado < 0 || grado >= n_puntos){
                throw std::invalid_argument("Grado invalido");
            }

            //Encontrar la posicion anterior y siguiente de x_int dentro de los datos originales
            for (int i = 0; i < x.size(); i++) {
                if (x[i] <= x_int) {
                    pos_ant = i;
                } else if (x[i] > x_int) {
                    pos_sig = i;
                    break;
                }
            }

            pos_inicial = pos_ant - n_puntos / 2;
            pos_final = pos_sig + n_puntos / 2;
            //Si n_puntos es par
            if (n_puntos % 2 == 0) {
                return interpolar(x_int, pos_inicial, pos_final);
            } else { //si n_puntos es impar
                pos_inicial_aux = pos_inicial + 1;
                pos_final_aux = pos_final - 1;

                //Validar posiciones
                if (pos_inicial_aux >= pos_final_aux || pos_final_aux >= n || pos_inicial_aux >= n || pos_inicial < 0 || pos_final >= n) {
                    return interpolar(x_int, pos_inicial, pos_final);
                }

                double y_int_1 = interpolar(x_int, pos_inicial, pos_final);
                double y_int_2 = interpolar(x_int, pos_inicial_aux, pos_final_aux);

                if (std::isnan(y_int_1)) {
                    return y_int_2;
                } else if(std::isnan(y_int_2)) {
                    return y_int_1;
                }

                // y_int_1 o y_int_2 son diferente de nan
                //Sacar los datos de x en el intervalo pos_inicial_aux, pos_final_aux con el dato adicional
                // con un for del x grande (pos_inicial) sacr los datos a x1 (0), x1 es un subvector de x que tiene desde x[pos_inicial_aux] hasta x[pos_final_aux]
                vector<double> x1 (x.begin() + pos_inicial, x.begin() + pos_final);

                //Sacar los datos de y en el intervalo pos_inicial_aux, pos_final_aux con el dato adicional
                vector<double> y1 (y.begin() + pos_inicial, y.begin() + pos_final);

                vector<double> F1 = newton::calcular_coeficientes(x1, y1);

                //Calcular el error
                double prod_1 = 1.0f; //Ultimo coeficiente de F1

                //Quitar el dato adicional del fin
                F1.erase(F1.end());

                //Calcular la productoria de R * (x_int - x1[0]) * (x_int - x1[1]) * ... * (x_int - x1[n_puntos - 1]) sin tener en cuenta el dato adicional
                for (int i = 0; i < F1.size(); i++) {
                    prod_1 *= (x_int - x1[i]);
                }
                double error_int_1 =  F1[F1.size() - 1] * prod_1 ;

                vector<double> x2 (x.begin() + pos_inicial_aux, x.begin() + pos_final_aux);

                //Sacar los datos de y en el intervalo pos_inicial_aux, pos_final_aux con el dato adicional
                vector<double> y2 (y.begin() + pos_inicial_aux, y.begin() + pos_final_aux);

                vector<double> F2 = newton::calcular_coeficientes(x2, y2);

                //Calcular el error
                double prod_2 = 1.0f; //Ultimo coeficiente de F1

                //Quitar el dato adicional del inicio
                F2.erase(F2.begin());

                //Calcular la productoria de R * (x_int - x1[0]) * (x_int - x1[1]) * ... * (x_int - x1[n_puntos - 1]) sin tener en cuenta el dato adicional
                for (int i = 0; i < F2.size(); i++) {
                    prod_2 *= (x_int - x1[i]);
                }
                double error_int_2 =  F2[F2.size() - 1] * prod_2;

                if (std::fabs(error_int_1) < std::fabs(error_int_2)) {
                    return y_int_1;
                } else {
                    return y_int_2;
                }
            }
            return NAN;
        }

        double interpolar(double x_int, int pos_inicial, int pos_final){
            /*
             * Validar que x_int este dentro del rango de x
             * Validar que pos_inicial y pos_final esten dentro del rango de x
             * Validar que pos_inicial sea menor que pos_final
             * Validar que pos_inicial y pos_final sean mayores que 0
             */
            if (x_int < x[pos_inicial] || x_int >= x[pos_final] || pos_inicial < 0 || pos_final >= x.size() || pos_inicial >= pos_final){
                return NAN;
            }

            /*
             * Crear subvectoes x e y del rango de pos_inicial a pos_final
             * Llama al metodo calcular coeficientes con los subvectores
             */
            vector<double> x1 (x.begin() + pos_inicial, x.begin() + pos_final);
            vector<double> y1 (y.begin() + pos_inicial, y.begin() + pos_final);
            vector<double> b_rango = calcular_coeficientes(x1, y1);

            if (b_rango.empty()){
                return NAN;
            }
            double f = b_rango[0];
            for (size_t i = 1; i < b_rango.size(); i++){
                double prod = 1;
                for (size_t j = 0; j < i; j++) {
                    prod *= (x_int - x1[j]);
                }

                f += prod * b_rango[i];
            }
            return f;
        }

        /**
         * @brief Calcula los coeficientes b0, b1, b2, ... del polinomio
         */
        static vector<double> calcular_coeficientes(vector<double> x, vector<double> y){
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
            return f[0];
        }

    private:
        vector<double> x; /*!<Variable independiente> */
        vector<double> y; /*!<Variable dependiente>*/
        vector<double> b; /*!<Vector de coeficientes>*/
    };
}

#endif