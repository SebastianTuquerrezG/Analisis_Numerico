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
	int opcion;
	char aux;
	vector<string> vectorFunciones;

    vectorFunciones.emplace_back("e^~x - ln(x)");
    vectorFunciones.emplace_back("x^3 + 4*(x^2) - 10");
    vectorFunciones.emplace_back("(e^(~x)) + x^2 - 2");
    vectorFunciones.emplace_back("(e^(~(x^2))) - x");
    vectorFunciones.emplace_back("(x-3)*(x-1)*(x-1)");
    vectorFunciones.emplace_back("(e^(-x^2)) - x");

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
		cout << "Ingrese su eleccion (1-5): ";
		
		if (!(cin >> opcion)) {
			cout << "Entrada no valida. Por favor, ingrese un numero valido." << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		
		cout << "\n";
		switch (opcion) {
		case 1:
            cout <<
			DatosBiseccion("x^2 - cos(x)");
			break;
		case 2:
			DatosReglaFalsa("x^2 - cos(x)");
			break;
		case 3:
			DatosBiseccion("x^3 + 4*x^2 - 10");
			break;
		case 4:
			DatosReglaFalsa("x^3 + 4*x^2 - 10");
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
	} while (opcion != 5 ); 
	
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


