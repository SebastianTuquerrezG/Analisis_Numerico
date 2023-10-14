#include <iostream>
#include <vector>

#include "newton.h"
#include "util.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::setprecision;

using interpolacion::newton;
using util::imprimir_tabla;

/**
 * @brief CASO 1newton - Diapositivas
 */
void caso_1_newton();

int main() {
    caso_1_newton();
    return 0;
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