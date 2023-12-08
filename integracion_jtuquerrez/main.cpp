/**
 * @file main.cpp
 * @author Sebastian Tuquerrez (jtuquerrez@unicauca.edu.co) - Cristian David Quinayas Rivera (crquinayas@unicauca.edu.co)
 * @brief Programa principal para la integracion de funciones o tablas de datos, mediante trapecio, simpson 1/3, simpson 3/8 y Romberg
 * @version 1.0.0
 * @date 2023-11-24
 *
 * @copyright Copyright (c) 2023
 */
#define USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Trapecio.h"
#include "SimpsonTercio.h"
#include "Simpson38.h"
#include "Simpson.h"
#include "Romberg.h"
#include "Derivacion.h"
#include "util.h"

using std::cout;
using std::string;
using std::vector;
using std::cin;
using std::endl;
using std::fixed;

using FuncPtr = std::function<void()>;

using integracion::trapecio;
using integracion::simpson13;
using integracion::simpson38;
using integracion::simpson;
using integracion::Romberg;
using derivacion::derivada;
using integracion::resultado_romberg;
using util::imprimir_tabla;
using util::crear_tabla;

/**
 * @brief Integracion usando el metodo del trapecio
 * @param title Titulo del caso
 * @param str_fn Funcion a integrar
 * @param str_dfn Segunda derivada
 */
void caso_trapecio(string title, string str_fn, string str_dfn);

/**
 * @brief Integracion de e^(x^2) por trapecio
 */
void caso_1_trapecio();

/**
 * @brief Integracion de sen(x)^2 por trapecio
 */
void caso_2_trapecio();

/**
 * @brief Integracion usando el metodo de simpson 1/3
 * @param title Contexto del problema
 * @param str_fn Funcion a integrar
 * @param str_dfn Cuarta deriva
 */
void caso_simpson13(string title, string str_fn, string str_dfn);

/**
 * @brief Integracion de e^(x^2) por simpson 1/3
 */
void caso_1_simpson13();

/**
 * @brief Integracion de sen(x)^2 por simpson 1/3
 */
void caso_2_simpson13();

/**
 * @brief Integracion de 10+2*x-6*x^2+5*x^4 por simpson 1/3
 */
void caso_3_simpson13();

/**
 * @brief Proyecto de integracion de momento X, momento Y y masa de la lamina por simpson 1/3
 */
void caso_proyecto_simpson13();

/**
 * @brief Integracion usando el metodo de simpson 3/8
 * @param title Contexto del caso
 * @param str_fn Funcion
 * @param str_dfn Cuarta derivada
 */
void caso_simpson38(string title, string str_fn, string str_dfn);

/**
 * @brief Integracion de e^(x^2) por simpson 3/8
 */
void caso_1_simpson38();

/**
 * @brief Integracion de sen(x)^2 por simpson 3/8
 */
void caso_2_simpson38();

/**
 * @brief Integracion de tablas de datos combinando metodos
 * @param title Contexto del caso
 * @param x vector de valores de la variable independiente
 * @param y vector de valores de la variable dependiente
 */
void caso_simpson(string title, vector<double> &x, vector<double> &y);

/**
 * @brief Integracion de tablas de datos caso 1
 */
void caso_1_simpson();

/**
 * @brief Integracion usando el metodo de Romberg
 * @param title
 * @param str_fn
 */
void caso_romberg(string title,
                  string str_fn);

/**
 * @brief Integracion de sen(x)^2 por romberg
 */
void caso_1_romberg();

/**
 * @brief Proyecto de integracion de momento X, momento Y y masa de la lamina por romberg
 */
void caso_proyecto_romberg();

/**
 * @brief Diferenciacion numerica
 * @param title Contexto del caso
 * @param str_fn Funcion
 */
void caso_diferenciacion(string title, string str_fn);

/**
 * @brief Diferenciacion numerica caso 1
 */
void caso_1_diferenciacion();

/**
 * @brief Proyecto de diferenciación para la función f(x)=xsen(x)
 */
void caso_proyecto_diferenciacion();

/**
 * @brief Salir del programa
 */
void salir();

int main() {
    map<string, FuncPtr> casos = {
        {"Caso 1. e^(x^2) trapecio", caso_1_trapecio},
        {"Caso 2. sen(x)^2 trapecio", caso_2_trapecio},
        {"Caso 1. e^(x^2) simpson13", caso_1_simpson13},
        {"Caso 2. sen(x)^2 simpson13", caso_2_simpson13},
        {"Caso 3. 10+2*x-6*x^2+5*x^4 simpson13", caso_3_simpson13},
        {"Caso 1. e^(x^2) simpson38", caso_1_simpson38},
        {"Caso 2. sen(x)^2 simpson38", caso_2_simpson38},
        {"Caso 1. e^(x^2) simpson", caso_1_simpson},
        {"Caso 1. sen(x)^2 romberg", caso_1_romberg},
        {"Diferenciacion numerica", caso_1_diferenciacion},
        {"Proyecto Simpson 1/3", caso_proyecto_simpson13},
        {"Proyecto Romberg", caso_proyecto_romberg},
        {"Proyecto Diferenciacion", caso_proyecto_diferenciacion},
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
                      string str_fn,
                      string str_dfn) {
    double a, b, n;
    cout << title << ":" << " por trapecio." << endl;

    cout << "Ingrese el limite inferior: " << endl;
    cin >> a;
    cout << "Ingrese el limite superior: " << endl;
    cin >> b;
    cout << "Ingrese la cantidad de segmentos: " << endl;
    cin >> n;

    //Instancia de trapecio
    trapecio t(str_fn, std::move(str_dfn), 1);

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
                  "e^(x^2)", //2*e^(x^2)*x
                  "4*(e^(x^2))*(x^2) + 2*(e^(x^2))");
}

void caso_2_trapecio() {
    caso_trapecio("Caso 2. sin(x)^2",
                  "sin(x)^2", //2*cos(x)*sen(x)
                  "2*cos(2*x)");
}

void caso_simpson13(string title,
                      string str_fn,
                      string str_dfn) {
    double a, b, n;
    int opcion;
    cout << title << ":" << " por simpson 1/3." << endl;

    cout << "Es polinomica si(1), o no(2)?" << endl;
    cin >> opcion;
    cout << "Ingrese el limite inferior: " << endl;
    cin >> a;
    cout << "Ingrese el limite superior: " << endl;
    cin >> b;
    cout << "Ingrese la cantidad de segmentos: " << endl;
    cin >> n;

    simpson13 s13(str_fn, std::move(str_dfn), opcion);

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
    caso_simpson13("Caso 1. e^(x^2)", //2*e^(x^2)*x, 4*(e^(x^2))*(x^2) + 2*(e^(x^2))
                  "e^(x^2)", //8*(e^(x^2))*(x^3) + 12*(e^(x^2))*(x)
                  "16*(e^(x^2))*(x^4) + 48*(e^(x^2))*(x^2) + 12*(e^(x^2))");
}

void caso_2_simpson13(){
    caso_simpson13("Caso 2. sin(x)^2", //2*cos(x)*sen(x), 2*cos(2*x)
                  "sin(x)^2", //-4*sin(2*x)
                  "-8*cos(2*x)");
}

void caso_3_simpson13(){
    caso_simpson13("Caso 3. 10+2*x-6*x^2+5*x^4",
                   "10+2*x-6*x^2+5*x^4",
                   "120");
}

void caso_proyecto_simpson13(){
    caso_simpson13("Momento X = ((sin(x-1) + cos(2.5*(x-1))^3)/2) * (sin(x-1) + cos(2.5*(x-1))^3)",
                   "((sin(x-1) + cos(2.5*(x-1))^3)/2) * (sin(x-1) + cos(2.5*(x-1))^3)",
                   "-9375*(cos(2.5*(x-1))^4)*(sin(2.5*(x-1))^2) + 1875*(cos(2.5*(x-1))^6) - 2568.75*(sin(2.5*(x-1))^2)*cos(2.5*(x-1))*sin(x-1)"
                   " + 933.8125*(cos(2.5*(x-1))^3)*sin(x-1) + 1342.5*(cos(2.5*(x-1))^2)*sin(2.5*(x-1))*cos(x-1) - 7031.25*(cos(2.5*(x-1))^2)"
                   "*(sin(2.5*(x-1))^2)*cos(5*(x-1)) - 375*(sin(2.5*(x-1))^3)*cos(x-1) - 4*cos(2*(x-1))");
    caso_simpson13("Momento Y = x*(sin(x-1) + cos(2.5*(x-1))^3)",
                   "x*(sin(x-1) + cos(2.5*(x-1))^3)",
                   "-x*sin(x-1) -2344.375*x*(sin(2.5(x-1))^2)*cos(2.5*(x-1)) +820.625*x*(cos(2.5*(x-1))^3) -2*cos(x-1) + 1312.625*(cos(2.5*(x-1))^2)*sin(2.5*(x-1))"
                   " - 375*(sin(2.5*(x-1))^3)");
    caso_simpson13("Masa de la lamina = sin(x-1) + cos(2.5*(x-1))^3",
                       "sin(x-1) + cos(2.5*(x-1))^3",
                   "sin(x-1) - 7.5(312.5*(sin(2.5*(x-1))^2)*cos(2.5*(x-1)) - 109.375*cos(2.5*(x-1))^3)");
}

void caso_simpson38(string title,
                      string str_fn,
                      string str_dfn) {
    double a, b, n;
    cout << title << ":" << " por simpson 3/8." << endl;

    cout << "Ingrese el limite inferior: " << endl;
    cin >> a;
    cout << "Ingrese el limite superior: " << endl;
    cin >> b;
    cout << "Ingrese la cantidad de segmentos: " << endl;
    cin >> n;

    simpson38 s38(str_fn, std::move(str_dfn));

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
                  "e^(x^2)",
                   "16*(e^(x^2))*(x^4) + 48*(e^(x^2))*(x^2) + 12*(e^(x^2))");
}

void caso_2_simpson38(){
    caso_simpson38("Caso 2. sin(x)^2",
                  "sin(x)^2",
                  "-8*cos(2*x)");
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

void caso_romberg(string title,
                   string str_fn) {

    double a, b, k;
    cout << title << ":" << " por trapecio." << endl;

    cout << "Ingrese el limite inferior: " << endl;
    cin >> a;
    cout << "Ingrese el limite superior: " << endl;
    cin >> b;
    cout << "Ingrese la cantidad de aproximaciones: " << endl;
    cin >> k;

    //Instancia de trapecio
    Romberg r(str_fn);

    resultado_romberg res = r.calcular(a, b, k);

    cout << "Valor de la integral: "
         << "entre: "
         << a << " y "
         << b << " con "
         << k << " aproximaciones = "
         << std::setprecision(10) << res.valor << endl
         << "Valor del error: " << res.error << endl;
}

void caso_1_romberg(){
    caso_romberg("Caso 1. sen(x)^2",
                 "(sin(x))^2");
}

void caso_proyecto_romberg(){
    caso_romberg("Momento X = ((sin(x-1) + cos(2.5*(x-1))^3)/2) * (sin(x-1) + cos(2.5*(x-1))^3)",
                 "((sin(x-1) + cos(2.5*(x-1))^3)/2) * (sin(x-1) + cos(2.5*(x-1))^3)");
    caso_romberg("Momento Y = x*(sin(x-1) + cos(2.5*(x-1))^3)",
                 "x*(sin(x-1) + cos(2.5*(x-1))^3)");
    caso_romberg("Masa de la lamina = sin(x-1) + cos(2.5*(x-1))^3",
                 "sin(x-1) + cos(2.5*(x-1))^3");
}

void caso_diferenciacion(string title, string str_fn) {
    double xi, paso, resultado;
    int diferencias, direccion, der;

    derivada d(str_fn);

    cout << title << endl;

    cout << "Ingrese 1 para primera derivada o 2 para segunda derivada: " << endl;
    cin >> der;
    cout << "Ingrese el x donde desea derivar: " << endl;
    cin >> xi;
    cout << "Ingrese el paso: " << endl;
    cin >> paso;
    cout << "Ingrese la cantidad de diferencias: " << endl;
    cin >> diferencias;
    cout << "Ingrese la direccion (0 para Adelante, 1 para Atras o 2 para central): " << endl;
    cin >> direccion;

    switch (der) {
        case 1:
            resultado = d.primeraDerivada(xi, paso, diferencias, direccion);
            break;
        case 2:
            resultado = d.segundaDerivada(xi, paso, diferencias, direccion);
            break;
    }

    cout << "La derivada de la funcion evaluada en el punto x = " << xi << " es: " << setprecision(5) << resultado << endl;
}

void caso_1_diferenciacion(){
    caso_diferenciacion("Caso 1. f(x) = - 0.1x^4 - 0.15x^3 - 0.5x^2 - 0.25x + 1.2",
                 "~0.1*x^4 - 0.15*x^3 - 0.5*x^2 - 0.25*x + 1.2");
}

void caso_proyecto_diferenciacion(){
    caso_diferenciacion("Funcion a derivar: f(x) = xsen(x)",
                        "x*sin(x)");
}