#include <iostream>
#include <string>
#include <vector>

#include "regresion.h"

using std::cout;
using std::endl;
using std::vector;

using regresion::solucion_lineal;
using regresion::lineal_simple;
using regresion::imprimir_tabla;

/**
 * @brief
 */
void caso_1_regresion();

/**
 * @brief Caso 1: Snatch damas
 */
void caso_1_snatch_damas();

int main() {
    // TODO: investigar IOTA
    caso_1_regresion();
    return 0;
}

void caso_1_regresion(){
    cout << "Caso 1" << endl;
    vector<double> x = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f};
    vector<double> y = {0.5f, 2.5f, 2.0f, 4.0f, 3.5f, 6.0f, 5.5f};

    //imprimir tabla TODO
    imprimir_tabla(x, y);

    lineal_simple ls(x, y);
    solucion_lineal sol = ls.calcular();

    //Imprimir la solucion
    sol.imprimir();
}
void caso_1_snatch_damas(){
    // TODO: Caso 1
}

