#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

#include "Trapecio.h"
#include "util.h"

using std::cout;
using std::endl;

using integracion::trapecio;
using util::imprimir_tabla;

/**
 * @brief Integracion usando el metodo del trapecio
 * @param title Titulo del caso
 * @param str_fn Funcion a integrar
 * @param a limite inferior
 * @param b limite superior
 * @param n cantidad de segmentos
 */
void caso_trapecio(string title,
                      string str_fn,
                      double a,
                      double b,
                      int n);

void caso_1_trapecio();

int main() {
    caso_1_trapecio();
    return 0;
}

void caso_trapecio(string title,
                      string str_fn,
                      double a,
                      double b,
                      int n) {
    cout << title << endl;

    //Instancia de trapecio
    trapecio t(str_fn);

    vector<double> x;
    vector<double> y;

    t.crear_tabla(x, y, a, b, n);

    //Imprime la tabla
    imprimir_tabla(x, y, "X", "Y", title);

    //Calcular el valor de la integral
    double valor = t.calcular(a, b, n);

    cout << "Valor de la integral: "
        << "entre: "
        << a << " y "
        << b << " = "
        << valor << endl;
};

void caso_1_trapecio() {
    caso_trapecio("Caso 1. e^(x^2)",
                  "e^(x^2)",
                  0.0f,
                  1.0f,
                  10);
}