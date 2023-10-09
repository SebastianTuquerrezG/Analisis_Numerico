#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

using std::vector;

/**
 * Clases / Funciones util
 */
namespace util{
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
}

#endif
