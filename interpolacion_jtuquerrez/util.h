/**
 * @file util.h
 * @brief Funciones de utilidad
 */
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <iomanip>

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

        size_t x_width = x_label.length() + 6;
        size_t y_width = y_label.length() + 10;
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
                 << X[i]
                 << setw(y_width)
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


    void imprimit_matriz(vector<vector<double>> m){
        for(size_t i = 0; i < m.size(); i++){
            for(size_t j = 0; j < m[i].size(); j++){
                cout << ((j > 0) ? " " : "")  <<  m[i][j] << " ";
            }
            cout << endl;
        }
    }
}

#endif
