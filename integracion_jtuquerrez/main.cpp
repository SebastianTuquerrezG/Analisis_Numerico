#include <iostream>
#include <string>
#include <vector>

#include "Trapecio.h"
#include "SimpsonTercio.h"
#include "Simpson38.h"
#include "Simpson.h"
#include "util.h"

using std::cout;
using std::string;
using std::vector;
using std::cin;
using std::endl;

using FuncPtr = std::function<void()>;

using integracion::trapecio;
using integracion::simpson13;
using integracion::simpson38;
using integracion::simpson;
using util::imprimir_tabla;
using util::crear_tabla;

/**
 * @brief Integracion usando el metodo del trapecio
 * @param title Titulo del caso
 * @param str_fn Funcion a integrar
 * @param a limite inferior
 * @param b limite superior
 * @param n cantidad de segmentos
 */
void caso_trapecio(string title,
                      string str_fn);

void caso_1_trapecio();

void caso_simpson13(string title,
                      string str_fn);

void caso_1_simpson13();

void caso_simpson38(string title,
                      string str_fn);

void caso_1_simpson38();

void caso_simpson(string title,
                      string str_fn);

void caso_1_simpson();

void salir();

int main() {
    map<string, FuncPtr> casos = {
        {"Caso 1. e^(x^2) trapecio", caso_1_trapecio},
        {"Caso 1. e^(x^2) simpson13", caso_1_simpson13},
        {"Caso 1. e^(x^2) simpson38", caso_1_simpson38},
        {"Caso 1. e^(x^2) simpson", caso_1_simpson},
        {"Salir", salir}
    };
    cout << "Integracion" << endl;
    int opcion;
    do{
        cout << endl;
        cout << "Seleccione una opcion: " << endl;
        int i = 1;
        for (auto &caso : casos) {
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
        cout << endl;
        std::advance(it, opcion - 1);
        it->second();
    } while (opcion != casos.size());
}

void caso_trapecio(string title,
                      string str_fn) {
    double a, b, n;
    cout << title << ":" << " por trapecio." << endl;

    cout << "Ingrese el limite inferior: " << endl;
    cin >> a;
    cout << "Ingrese el limite superior: " << endl;
    cin >> b;
    cout << "Ingrese la cantidad de segmentos: " << endl;
    cin >> n;

    //Instancia de trapecio
    trapecio t(str_fn);

    vector<double> x;
    vector<double> y;

    crear_tabla(x, y, a, b, n, str_fn);

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
                  "e^(x^2)");
}

void caso_simpson13(string title,
                      string str_fn) {
    double a, b, n;
    cout << title << ":" << " por simpson 1/3." << endl;

    cout << "Ingrese el limite inferior: " << endl;
    cin >> a;
    cout << "Ingrese el limite superior: " << endl;
    cin >> b;
    cout << "Ingrese la cantidad de segmentos: " << endl;
    cin >> n;

    simpson13 s13(str_fn);

    vector<double> x;
    vector<double> y;

    crear_tabla(x, y, a, b, n, str_fn);

    //Imprime la tabla
    imprimir_tabla(x, y, "X", "Y", title);

    //Calcular el valor de la integral
    double valor = s13.calcular(a, b, n);

    cout << "Valor de la integral: "
         << "entre: "
         << a << " y "
         << b << " = "
         << valor << endl;
}

void caso_1_simpson13(){
    caso_simpson13("Caso 1. e^(x^2)",
                  "e^(x^2)");
}

void caso_simpson38(string title,
                      string str_fn) {
    double a, b, n;
    cout << title << ":" << " por simpson 3/8." << endl;

    cout << "Ingrese el limite inferior: " << endl;
    cin >> a;
    cout << "Ingrese el limite superior: " << endl;
    cin >> b;
    cout << "Ingrese la cantidad de segmentos: " << endl;
    cin >> n;

    simpson38 s38(str_fn);

    vector<double> x;
    vector<double> y;

    crear_tabla(x, y, a, b, n, str_fn);

    //Imprime la tabla
    imprimir_tabla(x, y, "X", "Y", title);

    //Calcular el valor de la integral
    double valor = s38.calcular(a, b, n);

    cout << "Valor de la integral: "
         << "entre: "
         << a << " y "
         << b << " = "
         << valor << endl;
}

void caso_1_simpson38(){
    caso_simpson38("Caso 1. e^(x^2)",
                  "e^(x^2)");
}

void caso_simpson(string title,
                  vector<double> &x,
                  vector<double> &y) {
    cout << title << ":" << " por simpson." << endl;

    simpson s;

    imprimir_tabla(x, y, "X", "Y", title);

    double valor = s.calcular(x, y);

    cout << "Valor del area de la tabla de datos: "

         << valor << endl;
}

void caso_1_simpson(){
    vector<double> x = {0.00000, 0.04706, 0.09412, 0.14118, 0.18824, 0.23529, 0.28235, 0.32941, 0.37647, 0.42353, 0.47059, 0.51765, 0.56471, 0.61176, 0.65882, 0.70588, 0.75294, 0.80000};
    vector<double> y = {0.20000, 0.99959, 1.27640, 1.30746, 1.28600, 1.33258, 1.50611, 1.81498, 2.22811, 2.68604, 3.11198, 3.42294, 3.54075, 3.40317, 2.97498, 2.25901, 1.30727, 0.23200};
    caso_simpson("Caso 1. tabla de datos",
                  x,
                  y);
}

void salir(){
    cout << "Saliendo del programa. Hasta luego." << endl;
    exit(0);
}