/**
 * @file main.cpp
 * @author Joan Sebastian Tuquerrez Gomez (jtuquerrez@unicauca.edu.co)
 * @brief Programa principal de los metodos numericos para resolver ecuaciones de una sola variable
 * @version 1.0.0
 * @date 2023-09-15
 *
 * @copyright Copyright (c) 2023
 */

#include<iostream>
#include <string>
#include <cstdlib>
#include <vector>

#include "biseccion.h"
#include "newton_raphson.h"
#include "reglafalsa.h"
#include "Expression.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::system;
using std::vector;
using std::string;
using raices::newton_raphson;
using raices::biseccion;
using raices::reglafalsa;

/**
* @brief Solicitud de datos para calcular de la funcion ingresada dentro del intervalo dado utilizando el metodo de biseccion
* @param str_f Texto de la funcion a evaluar
*/
void DatosBiseccion(string str_f);

/**
* @brief Solicitud de datos para calcular de la funcion ingresada dentro del intervalo dado utilizando el metodo de regla falsa
* @param str_f Texto de la funcion a evaluar
*/
void DatosReglaFalsa(string str_f);

/**
 * @brief Solicitud de datos para calcular la funcion ingresada dentro del intervalo dado utilizando el metodo de newton_raphson
 * @param str_f Texto de la funcion a evaluar
 */
void DatosNewtonRaphson(string str_f);

/**
 * @brief Solicitud de datos para calcular la funcion ingresada dentro del intervalo dado utilizando el metodo de la secante
 * @param str_f Texto de la funcion a evaluar
 */
void DatosSecante(string str_f);

/**
 * @brief Solicitud de datos para calcular la funcion ingresada dentro del intervalo dado utilizando el metodo de newton generalizado
 * @param str_f Texto de la funcion a evaluar
 */
void DatosNewtonGeneralizado(string str_f);

/**
 * @brief Solicitud de datos para calcular la funcion ingresada dentro del intervalo dado utilizando el metodo de muller
 * @param str_f Texto de la funcion a evaluar
 */
void DatosMuller(string str_f);

int main (int argc, char *argv[]) {
	int opcionMetodo, opcionFuncion;
	char aux;
	vector<string> vectorFunciones;

    vectorFunciones.emplace_back("e^~x - ln(x),-(e^~x) - (1/x),e^~x + (1/(x^2))");
    vectorFunciones.emplace_back("x^3 + 4*(x^2) - 10,3*(x^2) + 8*x,6*x + 8");
    vectorFunciones.emplace_back("(e^(~x)) + x^2 - 2,-(e^(~x)) + 2*x,e^(~x) + 2");
    vectorFunciones.emplace_back("(e^(~(x^2))) - x,-2*x*e^(~(x^2)) - 1,-2*e^(~(x^2)) + 4*x^2*e^(~(x^2))");
    vectorFunciones.emplace_back("(x-3)*(x-1)*(x-1),3*(x^2) - 10*x + 7,6*x - 10");
    vectorFunciones.emplace_back("2*(e^~x) - sen(x),-2*(e^~x) - cos(x),2*(e^~x) + sen(x)");
    vectorFunciones.emplace_back("x^3 - 2*(x^2) - x + 1,3*(x^2) - 4*x - 1,6*x - 4");
    vectorFunciones.emplace_back("(x^10) - 1,10*(x^9),90*(x^8)");
    vectorFunciones.emplace_back("x^6 - 15*(x^4) + 14*(x^3) + 36*(x^2) - 24*x - 32,6*(x^5) - 60*(x^3) + 42*(x^2) + 72*x - 24,30*(x^4) - 180*(x^2) + 84*x + 72");
    vectorFunciones.emplace_back("2000 * ln(150000 / (150000 - 2700*x)) - (9.81 * x) - 750,(18000/(500-(9*x)))-(981/100),(162000/(500-(9*x)^2))");

	do {
		system("cls");
		cout << "\n";
		cout << "=================MENU=================" << endl;
		cout << "|| 1.Metodo de Biseccion           ||" << endl;
		cout << "|| 2.Metodo de la Regla Falsa      ||" << endl;
		cout << "|| 3.Metodo de Newton Raphson      ||" << endl;
		cout << "|| 4.Metodo de la Secante          ||" << endl;
        cout << "|| 5.Metodo de Newton Generalizado ||" << endl;
		cout << "|| 6.Salir                         ||" << endl;
        cout << vectorFunciones[0] << endl;
		cout << "Ingrese su eleccion (1-5): ";

        if (!(cin >> opcionMetodo)) {
            cout << "Entrada no valida. Por favor, ingrese un numero valido." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        cout << "\n";
        int contador = 1;
        for (const string & funcion : vectorFunciones) {
            size_t pos = funcion.find(",");
            string funcionCortada = funcion.substr(0, pos);
            cout << "Funcion " << contador << ": " << funcionCortada << endl;
            contador++;
        }
        cout << "Ingrese la funcion a evaluar (1-11): ";
        cin >> opcionFuncion;

		
		cout << "\n";
		switch (opcionMetodo) {
        case 1:
            break;
		case 6:
			cout << "Saliendo del programa..." << endl;
			break;
		default:
			cout << "Opcion no valida. Por favor, ingrese una opcion valida (1-5)." << endl;
		}
		
		cout << "\n";
		cout << "Presione una tecla para continuar....." << endl;
		cin.get(aux);
		cin.get(aux);
	} while (opcionMetodo != 5 );
	
	return 0;
}

void DatosBiseccion(string str_f) {
	double xa, xb, tol;
	int n;
	
	cout << "Metodo de biseccion" << endl;
	cout << "Funcion a evaluar: " << str_f << endl;
	cout << "Ingrese el valor inferior del intervalo: ";
	cin >> xa;
	cout << "Ingrese el valor superior del intervalo: ";
	cin >> xb;
	cout << "Ingrese la tolerancia (en porcentaje): ";
	cin >> tol;
	cout << "Ingrese el maximo numero de iteraciones: ";
	cin >> n;
	
	//Crear una instancia de biseccion pasando 
	//la funcion como parametro
	biseccion bis(str_f);
	
	solucion sol = bis.calcular(xa, xb, tol, n);
	
	sol.imprimir();
}

void DatosReglaFalsa(string str_f) {
	double xi, xs, tol;
	int n;
	
	cout << "Metodo de regla falsa" << endl;
	cout << "Funcion a evaluar: " << str_f << endl;
	cout << "Ingrese el valor inferior del intervalo: ";
	cin >> xi;
	cout << "Ingrese el valor superior del intervalo: ";
	cin >> xs;
	cout << "Ingrese la tolerancia (en porcentaje): ";
	cin >> tol;
	cout << "Ingrese el maximo numero de iteraciones: ";
	cin >> n;
	//Crear una instancia de regla falsa pasando 
	//la funcion como parametro
	
	reglafalsa rf(str_f);
	
	solucion sol = rf.calcular(xi, xs, tol, n);
	
	sol.imprimir();
}


