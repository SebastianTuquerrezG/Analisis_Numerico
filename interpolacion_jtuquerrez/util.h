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

}

#endif
