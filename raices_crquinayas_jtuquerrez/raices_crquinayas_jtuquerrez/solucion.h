#ifndef SOLUCION_H
#define SOLUCION_H

/**
 * @file solucion.h
 * @author Joan Sebastian Tuquerrez Gomez (jtuquerrez@unicauca.edu.co)
 * @brief libreria para imprimir las soluciones de los metodos numericos
 * @version 1.0.0
 * @date 2023-08-12
 *
 * @copyright Copyright (c) 2023
 */

#include <cfloat>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>

using std::cout;
using std::endl;
using std::setw;
using std::setprecision;
using std::vector;

namespace raices {
	
	/**
	* @brief Calcula el Error Relativo Porcentual entre dos aproximaciones
	* @param nueva Nueva aproximacion
	* @param anterior Aproximacion anterior
	*/
	double calcular_erp(double nueva, double anterior) {
		return fabs((nueva - anterior)/nueva) * 100.0f;
	}
	
	/**
	* @brief Aproximacion de una solucion
	*/
	struct aproximacion {
		double xAnt;/*!< Valor anterior */
		double xNueva;/*!< Valor anterior */
		double erp;/*!< Error relativo porcentual entre los dos valores */
	};
	
	/**
	* @brief Solucion a un metodo numerico para encontrar una raiz
	*/
	struct solucion {
		double raiz = NAN; /*!< Raiz encontrada, NAN si no se pudo hallar */
		vector<aproximacion> aproximaciones; /*!< Vector de aproximaciones */
		int iteraciones;
		
		/**
		* @brief Adiciona una nueva aproximacion
		* @param a Aproximacion
		*/
		void adicionar(aproximacion a) {
			aproximaciones.push_back(a);
		}
		
		void imprimir() {
			if (std::isnan(raiz)) {
				cout << "No se pudo obtener la raiz con los datos dados"<<endl;
			}else {
				cout << "La raiz es: " << raiz <<endl;
				cout << "Aproximaciones: "<< endl;
				cout << setw(20) << "1er aproximacion" << setw(20) << "2da aproximacion" << setw(20) << "Epr" << setw(20) << "No. iteracion" << endl;
				for (unsigned int i = 0; i< aproximaciones.size(); i++) {
					cout << setw(20)
						<< setprecision(10)
						<< aproximaciones[i].xAnt
						<< setw(20)
						<< setprecision(10)
						<< aproximaciones[i].xNueva
						<< setw(20)
						<<setprecision(10)
						<< aproximaciones[i].erp
						<< setw(20)
						<< i+1
						<<endl;
				}
			}
		}
	};
};

#endif
