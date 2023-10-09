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
using regresion::solucion_potencia;
using regresion::solucion_exponencial;
using regresion::solucion_cuadratica;

using regresion::imprimir_tabla;

using regresion::lineal_simple;
using regresion::exponencial;
using regresion::potencia;
using regresion::cuadratica;

/**
 * @brief Ejecuta un caso de regresion lineal
 * @param x Valores de la variable independiente
 * @param y Valores de la variable dependeiente
 * @param title Titulo del caso
 * @param x_label Etiqueta de la variable independiente para la tabla
 * @param y_label Etiqueta de la variable dependiente para la tabla
 * @param opcional_label Etiqueta opcional del contexto del caso
 * @param opcional Valores opcionales del contexto del caso
 */
void caso_regresion_lineal(const vector<double>& x,
                           const vector<double>& y,
                           const string& title,
                           const string& x_label = "",
                           const string& y_label = "",
                           const string& opcional_label = "",
                           const vector<double>& opcional = vector<double>());

/**
 * @brief Ejecuta un caso de regresion potencia
 * @param x Valores de la variable independiente
 * @param y Valores de la variable dependeiente
 * @param title Titulo del caso
 * @param x_label Etiqueta de la variable independiente para la tabla
 * @param y_label Etiqueta de la variable dependiente para la tabla
 * @param opcional_label Etiqueta opcional del contexto del caso
 * @param opcional Valores opcionales del contexto del caso
 */
void caso_regresion_potencia(const vector<double>& x,
                             const vector<double>& y,
                             const string& title,
                             const string& x_label = "",
                             const string& y_label = "",
                             const string& opcional_label = "",
                             const vector<double>& opcional = vector<double>());

/**
 * @brief Ejecuta un caso de regresion exponencial
 * @param x Valores de la variable independiente
 * @param y Valores de la variable dependeiente
 * @param title Titulo del caso
 * @param x_label Etiqueta de la variable independiente para la tabla
 * @param y_label Etiqueta de la variable dependiente para la tabla
 * @param opcional_label Etiqueta opcional del contexto del caso
 * @param opcional Valores opcionales del contexto del caso
 */
void caso_regresion_exponencial(const vector<double>& x,
                                 const vector<double>& y,
                                 const string& title,
                                 const string& x_label = "",
                                 const string& y_label = "",
                                 const string& opcional_label = "",
                                 const vector<double>& opcional = vector<double>());

/**
 * @brief Ejecuta un caso de regresion cuadratica
 * @param x Valores de la variable independiente
 * @param y Valores de la variable dependeiente
 * @param title Titulo del caso
 * @param x_label Etiqueta de la variable independiente para la tabla
 * @param y_label Etiqueta de la variable dependiente para la tabla
 * @param opcional_label Etiqueta opcional del contexto del caso
 * @param opcional Valores opcionales del contexto del caso
 */
void caso_regresion_cuadratica(const vector<double>& x,
                                const vector<double>& y,
                                const string& title,
                                const string& x_label = "",
                                const string& y_label = "",
                                const string& opcional_label = "",
                                const vector<double>& opcional = vector<double>());

/**
 * @brief Caso 1: Regresion lineal simple
 */
void caso_1_regresion();

/**
 * @brief Caso 2: Snatch damas
 */
void caso_snatch_damas();

/**
 * @brief Caso 3: Clean and Jerk
 */
void caso_clean_and_jerk();

/**
 * @brief Caso 4: Empresa industrial gastos por ventas
 */
void caso_empresa_industrial();

/**
 * @brief Caso 5: Produccion de trigo toneladas por precio de kilo
 */
void caso_produccion_trigo();

/**
 * @brief Caso 6: Bugs Project errores por lineas de codigo
 */
void caso_bugs_project();

/**
 * @brief Caso 1 de funcion potencia
 */
void caso_1_potencia();

/**
 * @brief Caso 1 de funcion exponencial
 */
void caso_1_exponencial();

/**
 * @brief Caso 1 de funcion cuadratica
 */
void caso_1_cuadratica();

/**
 * @brief Sale del programa
 */
void salir();

int main() {
    map<string , FuncPtr> casos = {
        {"Caso Regresion", caso_1_regresion},
        {"Caso Snatch Damas", caso_snatch_damas},
        {"Caso Clean and Jerk", caso_clean_and_jerk},
        {"Caso Empresa Industrial", caso_empresa_industrial},
        {"Caso Produccion Trigo", caso_produccion_trigo},
        {"Caso Bugs Project", caso_bugs_project},
        {"Caso Potencia", caso_1_potencia},
        {"Caso Exponencial", caso_1_exponencial},
        {"Caso Cuadratica", caso_1_cuadratica},
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
    } while (opcion != casos.size() + 1);
}

void caso_1_regresion(){
    string title = "Caso 1 Lineal Simple";
    vector<double> x = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f};
    vector<double> y = {0.5f, 2.5f, 2.0f, 4.0f, 3.5f, 6.0f, 5.5f};

    caso_regresion_lineal(x, y, title);
}

void caso_snatch_damas(){
    string title = "Caso Snath Damas";
    vector<double> x = {48.0f, 53.0f, 58.0f, 63.0f, 69.0f, 75.0f, 90.0f};
    vector<double> y = {98.0f, 103.0f, 112.0f, 117.0f, 123.0f, 135.0f, 130.0f};

    caso_regresion_lineal(x, y, title, "Peso Corporal (Kg)", "Peso Levantado (Kg)");
}

void caso_clean_and_jerk(){
    string title = "Caso Clean and Jerk";
    vector<double> x = {56.0f, 62.0f, 69.0f, 77.0f, 85.0f, 94.0f, 105.0f};
    vector<double> y = {171.0f, 183.0f, 198.0f, 214.0f, 220.0f, 233.0f, 246.0f};

    caso_regresion_lineal(x, y, title, "Peso Corporal (Kg)", "Peso Levantado (Kg)");
}

void caso_regresion_lineal(const vector<double>& x,
                           const vector<double>& y,
                           const string& title,
                           const string& x_label,
                           const string& y_label,
                           const string& opcional_label,
                           const vector<double>& opcional){
    //imprimir salto de linea
    cout << endl;
    cout << title << endl;

    imprimir_tabla(x, y, x_label, y_label, opcional_label, opcional);

    lineal_simple ls(x, y);
    solucion_lineal sol = ls.calcular();

    //Imprimir la solucion
    sol.imprimir();
    cout << endl;
}

void caso_regresion_potencia(const vector<double>& x,
                             const vector<double>& y,
                             const string& title,
                             const string& x_label,
                             const string& y_label,
                             const string& opcional_label,
                             const vector<double>& opcional){
    //imprimir salto de linea
    cout << endl;
    cout << title << endl;

    imprimir_tabla(x, y, x_label, y_label, opcional_label, opcional);

    potencia reg_potencia(x, y);
    solucion_potencia sol = reg_potencia.calcular();

    //Imprimir la solucion
    sol.imprimir();
    cout << endl;
}

void caso_regresion_exponencial(const vector<double>& x,
                                 const vector<double>& y,
                                 const string& title,
                                 const string& x_label,
                                 const string& y_label,
                                 const string& opcional_label,
                                 const vector<double>& opcional){
    //imprimir salto de linea
    cout << endl;
    cout << title << endl;

    imprimir_tabla(x, y, x_label, y_label, opcional_label, opcional);

    exponencial reg_exponencial(x, y);

    solucion_exponencial sol = reg_exponencial.calcular();

    //Imprimir la solucion
    sol.imprimir();
    cout << endl;
}

void caso_regresion_cuadratica(const vector<double>& x,
                                const vector<double>& y,
                                const string& title,
                                const string& x_label,
                                const string& y_label,
                                const string& opcional_label,
                                const vector<double>& opcional){
    //imprimir salto de linea
    cout << endl;
    cout << title << endl;

    imprimir_tabla(x, y, x_label, y_label, opcional_label, opcional);

    cuadratica reg_cuadratica(x, y);

    solucion_cuadratica sol = reg_cuadratica.calcular();

    //Imprimir la solucion
    sol.imprimir();
    cout << endl;
}

void caso_1_exponencial(){
    string title = "Caso 1 Exponencial";
    vector<double> x = {12.0f, 41.0f, 93.0f, 147.0f, 204.0f, 264.0f, 373.0f, 509.0f, 773.0f};
    vector<double> y = {930.0f, 815.0f, 632.0f, 487.0f, 370.0f, 265.0f, 147.0f, 76.0f, 17.0f};

    caso_regresion_exponencial(x, y, title);
}

void caso_1_potencia(){
    string title = "Caso 1 Potencia";
    vector<double> x = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f};
    vector<double> y = {1.06f, 1.33f, 1.52f, 1.68f, 1.81f, 1.91f, 2.01f, 2.11f};

    caso_regresion_potencia(x, y, title);
}

void caso_1_cuadratica(){
    string title = "Caso 1 Cuadratica";
    vector<double> x = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    vector<double> y = {2.1f, 7.7f, 13.6f, 27.2f, 40.9f, 61.1f};

    caso_regresion_cuadratica(x, y, title);
}

void caso_empresa_industrial(){
    string title = "Caso 2 Empresa Industrial";
    vector<double> x = {23.01f, 27.61f, 32.11f, 36.18f, 37.57f, 33.51f, 36.61f, 31.16f, 32.78f, 41.19f, 39.97f, 39.69f, 40.30f, 40.95f, 14.22f, 13.93f, 15.50f, 16.31f, 17.49f, 19.89f, 21.48f, 20.40f, 22.68f, 20.97f, 23.35f, 26.10f, 29.11f, 27.24f};
    vector<double> y = {163.43f, 172.49f, 180.52f, 190.51f, 196.50f, 196.02f, 200.83f, 196.77f, 205.34f, 220.23f, 228.70f, 236.50f, 244.56f, 254.77f, 95.07f, 97.28f, 103.16f, 107.61f, 113.86f, 121.15f, 129.10f, 132.34f, 142.86f, 143.12f, 147.93f, 155.96f, 164.95f, 163.92f};

    caso_regresion_lineal(x, y, title, "Gastos en Publicidad(millones de pesos)",
                          "Volumen en ventas(millones de pesos)");
}

void caso_produccion_trigo(){
    string title = "Caso Produccion Trigo";
    vector<double> x = {30.0f, 28.0f, 32.0f, 25.0f, 27.0f, 26.0f, 23.0f, 24.0f, 35.0f, 40.0f};
    vector<double> y = {25.0f, 30.0f, 27.0f, 40.0f, 42.0f, 40.0f, 50.0f, 45.0f, 30.0f, 25.0f};
    vector<double> anio = {1980, 1981, 1982, 1983, 1984, 1985, 1986, 1987, 1988, 1989};

    caso_regresion_lineal(x, y, title, "Produccion de trigo (miles de toneladas)",
                          "Precio del kilo de harina de trigo (pesos)", "Anio", anio);
}

void caso_bugs_project(){
    string title = "Caso Bugs Project";
    vector<double> x = {235.0f, 276.0f, 373.0f, 412.0f, 506.0f, 598.0f, 642.0f, 703.0f, 773.0f, 844.0f, 968.0f, 1164.0f};
    vector<double> y = {6.0f, 7.0f, 11.0f, 21.0f, 19.0f, 15.0f, 27.0f, 26.0f, 36.0f, 34.0f, 44.0f, 49.0f};

    caso_regresion_lineal(x, y, title, "Tamaño de modulo en LDC (lineas de codigo)", "Cantidad de errores detectados");
}

void salir(){
    cout << "Saliendo del programa. Hasta luego." << endl;
    exit(0);
}