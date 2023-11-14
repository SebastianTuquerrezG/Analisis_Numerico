#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "Trapecio.h"
#include "util.h"

using std::cout;
using std::string;
using std::vector;
using std::cin;
using std::endl;

using FuncPtr = std::function<void()>;

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
                      string str_fn);

void caso_1_trapecio();

void salir();

int main() {
    map<string, FuncPtr> casos = {
        {"Caso 1. e^(x^2)", caso_1_trapecio},
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
                  "e^(x^2)");
}

void salir(){
    cout << "Saliendo del programa. Hasta luego." << endl;
    exit(0);
}