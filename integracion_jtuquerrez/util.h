/**
 * @file util.h
 * @author Sebastian Tuquerrez (jtuquerrez@unicauca.edu.co) - Cristian David Quinayas Rivera (crquinayas@unicauca.edu.co)
 * @brief Funciones de utilidad para el proyecto
 * @version 1.0.0
 * @date 2023-11-24
 *
 * @copyright Copyright (c) 2023
 */

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <iomanip>

#include "Expression.h"

using std::cout;
using std::endl;
using std::vector;
using std::setw;
using std::setprecision;
using std::string;

namespace util{
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
     * Imprime una tabla de datos
     * @param X  variable independiente
     * @param y variable dependiente
     * @param x_label Etiqueta de la variable independiente
     * @param y_label Etiqueta de la variable dependiente
     * @param title Titulo de la tabla
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

        size_t x_width = x_label.length() + 12;
        size_t y_width = y_label.length() + 12;
        size_t title_width = title.length() + 6;
        size_t delineacion = x_width + y_width + title_width + 5;
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
                 << setprecision(5)
                 << X[i]
                 << setw(y_width)
                 << setprecision(5)
                 << Y[i]
                 <<endl;
        }
        cout << str_repeat("=", delineacion) << endl;
    }

    /**
     * Eliminacion de Gauss para una matriz de reales
     * @param m Matriz
     * @return Vector de Coeficientes
     */
    vector<double> gauss(vector<vector<double>> m) {
        int i, j, k;
        int n = m.size();
        vector<double> resultado(n);
        //pivoteo: Para cada fila i, buscar en la columna i el valor mayor
        //e intercambiar la fila i por la que contenga el valor mayor.
        for (i = 0; i < n - 1; i++) {
            for (j = i + 1; j < n; j++) {
                if (m[i][j] > m[i][i]) {
                    std::swap(m[i], m[j]);
                }
            }
        }

        //Eliminacion gaussiana
        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                double v = m[j][i] / m[i][i]; //Valor que anula el elemento en la columna
                //Hacer la operacion fila[j] = fila[j] - v * fila[i]
                for(k=0; k <= n; k++) {
                    m[j][k] -= v * m[i][k];
                }
            }
        }
        //Despejar las variables
        for (i= n - 1; i >= 0; i--) {
            resultado[i] = m[i][n];
            //reemplazar las variables ya halladas
            for (j = i + 1; j < n; j++) {
                if (i != j) { //reeemplazar las variables, menos el coeficiente
                    resultado[i] = resultado[i] - m[i][j] * resultado[j];
                }
            }
            resultado[i] = resultado[i] / m[i][i];
        }
        return resultado;
    }

    /**
     * @brief Imprime una matriz 2x2
     * @param m Matriz a imprimir
     */
    void imprimit_matriz(vector<vector<double>> m){
        for(size_t i = 0; i < m.size(); i++){
            for(size_t j = 0; j < m[i].size(); j++){
                cout << ((j > 0) ? " " : "")  <<  m[i][j] << " ";
            }
            cout << endl;
        }
    }

    /**
     * @brief Construye una tabla de datos espaciados uniformemente
     * @param x Referencia al vector donde se almacenaran los valores de x
     * @param y Referencia al vector donde se almacenaran los valores de y
     * @param a Limite inferior
     * @param b Limite Superior
     * @param n Cantidad de Segmentos
     * @param f_str Texto de la funcion
     */
    void crear_tabla(vector<double> &x,
                     vector<double> &y,
                     double a,
                     double b,
                     int n,
                     string f_str){
        Expression f(std::move(f_str));

        x.resize(n + 1);
        y.resize(n + 1);

        //Calcular el paso
        double h = (b - a) / (double) n;
        double xi = a;

        for (int i = 0; i <= n; i++) {
            x[i] = xi;
            y[i] = f(xi);
            xi += h;
        }
    }

    /**
     * @brief Calcula el maximo de una derivada n
     * @param derivada derivada n de la funcion
     * @param a limite inferior
     * @param b limite superior
     * @return el punto maximo en el intervalo de la derivada
     */
    double calcularMaximo(string derivada, double a, double b){
        Expression f(std::move(derivada));

        double max = f(a);
        double xi = a;
        double h =  (b - a) / 100.0;

        for (int i = 0; i <= b; i++) {
            double y = f(xi);
            if(y > max) max = y;
            xi += h;
        }

        return fabs(max);
    }

    /**
     * @brief Calcula un punto en la derivada n
     * @param derivada derivada n de la funcion
     * @param punto punto a evaluar
     * @return valor del punto en la derivada n
     */
    double calcularPunto(string derivada, double punto){
        Expression f(std::move(derivada));

        double max = f(punto);

        return max;
    }
}

#endif