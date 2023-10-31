#include <iostream>
#include <vector>

#include "newton.h"
#include "util.h"
#include "lagrange.h"
#include "spline3.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::setprecision;

using interpolacion::newton;
using interpolacion::lagrange;
using interpolacion::spline3;
using util::imprimir_tabla;

/**
 * @brief CASO INTERPOLACION
 * @param x Vector de x
 * @param y Vector de y
 * @param opcion Opcion de interpolacion
 */
void caso_interpolacion(vector<double> x, vector<double> y, int opcion) ;

/**
 * @brief CASO 1newton - Diapositivas
 */
void caso_1_newton();

/**
 * @brief CASO 1 lagrange
 */
void caso_1_lagrange();

/**
 * @brief Caso 1 Trazadores Cubicos
 */
void caso_1_spline3();

int main() {
    //caso_1_newton();
    //caso_1_lagrange();
    caso_1_spline3();
    return 0;
}

void caso_interpolacion(vector<double> x, vector<double> y, int opcion) {

}

void caso_1_newton(){
    vector<double> x = {100.0f, 200.0f, 300.0f, 400.0f, 500.0f};
    vector<double> y = {-160.0f, -35.0f, -4.2f, 9.0f, 16.9f};

    //Crear una instancia de newton
    newton n(x, y);

    //Imprimir el polinomio interpolante
    cout << "Polinomio interpolante: " << n.polinomio() << endl;

    double x_int, y_int;
    int opcion;

    cout << "Interpolacion por diferencias divididas de newton" << endl;

    //Imprimir tabla de datos
    imprimir_tabla(x, y, "Temperatura (k)", "B (cm3/mol)");

    //Pedir valor de x a interpolar
    do {
        do{
            cout << "Introduzca el valor de x a interpolar: ";
            cin >> x_int;
        } while (x_int < x[0] || x_int > x[x.size() - 1]);

        y_int = n.interpolar(x_int);

        cout << "El valor de y para x = " << x_int << " es: " << y_int << endl;

        cout << "Desea interpolar otro valor? (1 = si, 0 = no): ";
    } while (cin >> opcion && opcion == 1);
    cout << endl;
    cout << "Fin del programa" << endl;
    cin.get();
}

void caso_1_lagrange(){
    vector<double> x = {100.0f, 200.0f, 300.0f, 400.0f, 500.0f};
    vector<double> y = {-160.0f, -35.0f, -4.2f, 9.0f, 16.9f};

    //Crear una instancia de newton
    lagrange l(x, y);

    //Imprimir el polinomio interpolante
    cout << "Polinomio interpolante: " << l.polinomio() << endl;

    double x_int, y_int;
    int opcion;

    cout << "Interpolacion mediante el metodo de lagrange" << endl;

    //Imprimir tabla de datos
    imprimir_tabla(x, y, "Temperatura (k)", "B (cm3/mol)");

    //Pedir valor de x a interpolar
    do {
        do{
            cout << "Introduzca el valor de x a interpolar: ";
            cin >> x_int;
        } while (x_int < x[0] || x_int > x[x.size() - 1]);

        y_int = l.interpolar(x_int,3);

        cout << "El valor de y para x = " << x_int << " es: " << y_int << endl;

        cout << "Desea interpolar otro valor? (1 = si, 0 = no): ";
    } while (cin >> opcion && opcion == 1);
    cout << endl;
    cout << "Fin del programa" << endl;
    cin.get();
}

void caso_1_spline3(){
    vector<double> x = {3.0f, 4.5f, 7.0f, 9.0f};
    vector<double> y = {2.5f, 1.0f, 2.5f, 0.5f};

    //Crear una instancia de newton
    spline3 s3(x, y);

    //Imprimir el polinomio interpolante
    //cout << "Polinomio interpolante: " << l.polinomio() << endl;

    double x_int, y_int;
    int opcion;

    cout << "Interpolacion mediante Trazadores cubicos" << endl;

    //Imprimir tabla de datos
    imprimir_tabla(x, y, "Temperatura (k)", "B (cm3/mol)");

    //Pedir valor de x a interpolar
    do {
        do{
            cout << "Introduzca el valor de x a interpolar: ";
            cin >> x_int;
        } while (x_int < x[0] || x_int > x[x.size() - 1]);

        y_int = s3.interpolar(x_int);

        cout << "El valor de y para x = " << x_int << " es: " << y_int << endl;

        cout << "Desea interpolar otro valor? (1 = si, 0 = no): ";
    } while (cin >> opcion && opcion == 1);
    cout << endl;
    cout << "Fin del programa" << endl;
    cin.get();
}