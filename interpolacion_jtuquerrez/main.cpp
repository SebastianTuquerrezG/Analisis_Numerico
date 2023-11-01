#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <map>
#include <functional>

#include "newton.h"
#include "util.h"
#include "lagrange.h"
#include "spline3.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::setprecision;
using std::string;
using std::map;

using FuncPtr = std::function<void()>;

using interpolacion::newton;
using interpolacion::lagrange;
using interpolacion::spline3;
using util::imprimir_tabla;

double  x_int = 0.0f, y_int = 0.0f, error_sup, error_inf; //Variables globales
int opcion_int = 0, grado;

/**
 * @brief CASO INTERPOLACION mediante newton
 * @param x Vector de x
 * @param y Vector de y
 * @param opcion Opcion de interpolacion
 */
void caso_interpolacion_newton(vector<double> x,
                               vector<double> y,
                               const string& title,
                               const string& x_label = "",
                               const string& y_label = "",
                               const string& opcional_label = "",
                               const vector<double>& opcional = vector<double>());

/**
 * @brief CASO INTERPOLACION mediante lagrange
 * @param x Vector de x
 * @param y Vector de y
 * @param opcion Opcion de interpolacion
 */
void caso_interpolacion_lagrange(vector<double> x,
                                 vector<double> y,
                                 const string& title,
                                 const string& x_label = "",
                                 const string& y_label = "",
                                 const string& opcional_label = "",
                                 const vector<double>& opcional = vector<double>());

/**
 * @brief CASO INTERPOLACION mediante trazadores cubicos
 * @param x Vector de x
 * @param y Vector de y
 * @param opcion Opcion de interpolacion
 */
void caso_interpolacion_trazadores(vector<double> x,
                                   vector<double> y,
                                   const string& title,
                                   const string& x_label = "",
                                   const string& y_label = "",
                                   const string& opcional_label = "",
                                   const vector<double>& opcional = vector<double>());

/**
 * @brief CASO 1newton - Diapositivas
 */
void caso_1_newton();

/**
 * @brief CASO 2 newton - Diapositivas
 */
void caso_2_newton();

/**
 * @brief CASO 1 lagrange
 */
void caso_1_lagrange();

/**
 * @brief Caso 1 Trazadores Cubicos
 */
void caso_1_spline3();

/**
 * @brief Caso 2 Trazadores Cubicos
 */
void caso_2_spline3();

/**
 * @brief Salir del programa
 */
void salir();

int main() {
    map<string , FuncPtr> casos = {
            {"Caso 1 Newton", caso_1_newton},
            {"Caso 2 Proyecto Newton", caso_2_newton},
            {"Caso Lagrange", caso_1_lagrange},
            {"Caso Trazadores Cubicos", caso_1_spline3},
            {"Caso 2 Proyecto Trazadores cubicos", caso_2_spline3},
            {"Salir", salir}
    };
    cout << "Interpolacion" << endl;
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

void caso_interpolacion_newton(vector<double> x,
                               vector<double> y,
                               const string& title,
                               const string& x_label,
                               const string& y_label,
                               const string& opcional_label,
                               const vector<double>& opcional) {
    newton n(x, y);

    cout << "Interpolacion por diferencias divididas de newton" << endl;

    cout << title << endl;

    cout << "Polinomio interpolante: " << n.polinomio() << endl;

    imprimir_tabla(x, y, x_label, y_label, opcional_label, opcional);

    do {
        do {
            cout << "Introduzca el valor de x a interpolar: ";
            cin >> x_int;
            cout << "Introduzca el grado del polinomio: <= "
                << x.size() - 1 << ", o 0 para usar todos los datos" <<  endl;
            cin >> grado;
        } while (x_int < x[0] || x_int > x[x.size() - 1] || grado < 0 || grado > x.size() - 1);

        if (grado == 0){
            y_int = n.interpolar(x_int);
        } else{
            y_int = n.interpolar(x_int, grado);
            error_sup = n.calcular_error_int(x_int, 0, grado);
            error_inf = n.calcular_error_int(x_int, 1, grado + 1);
        }

        cout << " Error(Superior): " << error_sup << ", Error(Inferior): " << error_inf << endl;

        cout << "El valor de y para x = " << x_int << " es: " << y_int << endl;

        cout << endl;
        cout << "Desea interpolar otro valor? (1 = si, 0 = no): ";
    } while (cin >> opcion_int && opcion_int == 1);
}

void caso_1_newton(){
    vector<double> x = {100.0f, 200.0f, 300.0f, 400.0f, 500.0f};
    vector<double> y = {-160.0f, -35.0f, -4.2f, 9.0f, 16.9f};

    caso_interpolacion_newton(x, y, "Caso 1 Newton", "Temperatura (k)", "B (cm3/mol)");
}

void caso_2_newton(){
    vector<double> x = {43.0f, 50.0f, 56.0f, 60.0f, 63.0f, 69.0f, 74.0f};
    vector<double> y = {0.041301f, 0.100248f, 0.124555, 0.128347f, 0.125552f, 0.108262f, 0.085188f};

    caso_interpolacion_newton(x, y, "Caso 2 Proyecto Newton");
}

void caso_interpolacion_lagrange(vector<double> x,
                                 vector<double> y,
                                 const string& title,
                                 const string& x_label,
                                 const string& y_label,
                                 const string& opcional_label,
                                 const vector<double>& opcional) {
    lagrange l(x, y);

    cout << "Interpolacion por lagrange" << endl;

    cout << title << endl;

    cout << "Polinomio interpolante" << l.polinomio() << endl;

    imprimir_tabla(x, y, x_label, y_label, opcional_label, opcional);

    do {
        do {
            cout << "Introduzca el valor de x a interpolar: ";
            cin >> x_int;
            cout << "Introduzca el grado del polinomio: <= "
                    << x.size() - 1 << ", o 0 para usar todos los datos" <<  endl;
            cin >> grado;
        } while (x_int < x[0] || x_int > x[x.size() - 1] || grado < 0 || grado > x.size() - 1);

        if (grado == 0){
            y_int = l.interpolar(x_int);
        } else{
            y_int = l.interpolar(x_int, grado);
        }

        cout << "El valor de y para x = " << x_int << " es: " << y_int << endl;

        cout << endl;
        cout << "Desea interpolar otro valor? (1 = si, 0 = no): ";
    } while (cin >> opcion_int && opcion_int == 1);
}

void caso_1_lagrange(){
    vector<double> x = {100.0f, 200.0f, 300.0f, 400.0f, 500.0f};
    vector<double> y = {-160.0f, -35.0f, -4.2f, 9.0f, 16.9f};

    caso_interpolacion_lagrange(x, y, "Caso 1 Lagrange", "Temperatura (k)", "B (cm3/mol)");
}

void caso_interpolacion_trazadores(vector<double> x,
                                   vector<double> y,
                                   const string& title,
                                   const string& x_label,
                                   const string& y_label,
                                   const string& opcional_label,
                                   const vector<double>& opcional) {
    cout << "Interpolacion por trazadores cubicos" << endl;

    cout << title << endl;

    //cout << "Polinomio interpolante" << s3.polinomio() << endl;

    imprimir_tabla(x, y, x_label, y_label, opcional_label, opcional);

    spline3 s3(x, y);

    do {
        do{
            cout << "Introduzca el valor de x a interpolar: ";
            cin >> x_int;
        } while (x_int < x[0] || x_int > x[x.size() - 1]);

        y_int = s3.interpolar(x_int);

        cout << "El valor de y para x = " << x_int << " es: " << y_int << endl;

        cout << endl;
        cout << "Desea interpolar otro valor? (1 = si, 0 = no): ";
    } while (cin >> opcion_int && opcion_int == 1);
}

void caso_1_spline3(){
    vector<double> x = {3.0f, 4.5f, 7.0f, 9.0f};
    vector<double> y = {2.5f, 1.0f, 2.5f, 0.5f};

    caso_interpolacion_trazadores(x, y, "Caso 1 Trazadores Cubicos", "Temperatura (k)", "B (cm3/mol)");
}

void caso_2_spline3() {
    vector<double> x = {43.0f, 50.0f, 56.0f, 60.0f, 63.0f, 69.0f, 74.0f};
    vector<double> y = {0.041301f, 0.100248f, 0.124555, 0.128347f, 0.125552f, 0.108262f, 0.085188f};

    caso_interpolacion_trazadores(x, y, "Caso 2 Proyecto Trazadores Cubicos");
}

void salir(){
    cout << "Saliendo del programa. Hasta luego." << endl;
    exit(0);
}