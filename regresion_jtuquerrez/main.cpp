#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

#include "regresion.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::cin;
using std::map;

using FuncPtr = std::function<void()>;

using regresion::solucion_lineal;
using regresion::lineal_simple;
using regresion::imprimir_tabla;

/**
 * @brief Ejecuta un caso de regresion lineal
 * @param x Valores de la variable independiente
 * @param y Valores de la variable dependeiente
 * @param title Titulo del caso
 * @param x_label Etiqueta de la variable independiente para la tabla
 * @param y_label Etiqueta de la variable dependiente para la tabla
 */
void caso_regresion(const vector<double>& x,
                    const vector<double>& y,
                    const string& title,
                    const string& x_label = "",
                    const string& y_label = "");
/**
 * @brief Caso 1: Regresion lineal simple
 */
void caso_1_regresion();

/**
 * @brief Caso 1: Snatch damas
 */
void caso_snatch_damas();

/**
 * @brief Caso 2: Clean and Jerk
 */
void caso_clean_and_jerk();

/**
 * @brief Caso 1: Empresa industrial gastos por ventas
 */
void caso_1_empresa_industrial();

/**
 * @brief Caso 2: Empresa industrial gastos por ventas
 */
void caso_2_empresa_industrial();

/**
 * @brief Caso 1: Produccion de trigo toneladas por precio de kilo
 */
void caso_produccion_trigo();

/**
 * @brief Caso 1: Bugs Project errores por lineas de codigo
 */
void caso_bugs_project();

/**
 * @brief Sale del programa
 */
void salir();

int main() {
    map<string , FuncPtr> casos = {
        {"Caso Rregresion", caso_1_regresion},
        {"Caso Snatch Damas", caso_snatch_damas},
        {"Caso Clean and Jerk", caso_clean_and_jerk},
        {"Caso 1 Empresa Industrial", caso_1_empresa_industrial},
        {"Caso 2 Empresa Industrial", caso_2_empresa_industrial},
        {"Caso Produccion Trigo", caso_produccion_trigo},
        {"Caso Bugs Project", caso_bugs_project},
        {"Salir", salir}
    };

    int opcion = 0;
    do {
        cout << "Seleccione un caso:" << endl;
        int i = 1;
        for (auto& caso : casos) {
            cout << i << ". " << caso.first << endl;
            i++;
        }
        cout << "Opcion: ";
        cin >> opcion;
        if (opcion < 1 || opcion > casos.size()) {
            cout << "Opcion invalida" << endl;
            continue;
        }
        auto it = casos.begin();
        std::advance(it, opcion - 1);
        it->second();
    } while (opcion == casos.size() + 1);
}

void caso_1_regresion(){
    string title = "Caso 1";
    vector<double> x = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f};
    vector<double> y = {0.5f, 2.5f, 2.0f, 4.0f, 3.5f, 6.0f, 5.5f};

    caso_regresion(x, y, title);
}

void caso_snatch_damas(){
    string title = "Caso Snath Damas";
    vector<double> x = {48.0f, 53.0f, 58.0f, 63.0f, 69.0f, 75.0f, 90.0f};
    vector<double> y = {98.0f, 103.0f, 112.0f, 117.0f, 123.0f, 135.0f, 130.0f};

    caso_regresion(x, y, title, "Peso Corporal (Kg)", "Peso Levantado (Kg)");
}

void caso_clean_and_jerk(){
    string title = "Caso Clean and Jerk";
    vector<double> x = {56.0f, 62.0f, 69.0f, 77.0f, 85.0f, 94.0f, 105.0f};
    vector<double> y = {171.0f, 183.0f, 198.0f, 214.0f, 220.0f, 233.0f, 246.0f};

    caso_regresion(x, y, title, "Peso Corporal (Kg)", "Peso Levantado (Kg)");
}

void caso_regresion(const vector<double>& x,
                    const vector<double>& y,
                    const string& title,
                    const string& x_label,
                    const string& y_label){
    cout << title << endl;

    imprimir_tabla(x, y, x_label, y_label);

    lineal_simple ls(x, y);
    solucion_lineal sol = ls.calcular();

    //Imprimir la solucion
    sol.imprimir();
}

void caso_1_empresa_industrial(){
}

void caso_2_empresa_industrial(){
}

void caso_produccion_trigo(){
}

void caso_bugs_project(){
}

void salir(){
    cout << "Saliendo del programa. Hasta luego." << endl;
    exit(0);
}
