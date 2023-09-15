#ifndef SECANTE_H
#define SECANTE_H

/**
 * @file secante.h
 * @author Joan Sebastian Tuquerrez Gomez (jtuquerrez@unicauca.edu.co)
 * @brief libreria que implementa el metodo de la secante
 * @version 1.0.0
 * @date 2023-09-01
 *
 * @copyright Copyright (c) 2023
 */

#include <string>

#include "Expression.h"
#include "solucion.h"

using std::string;
using raices::solucion;
using raices::calcular_erp;
using raices::es_cero;

namespace raices {
	/**
	* @brief Implementacion del metodo de la Secante
	*/
	class secante {
	public:
		/**
		* @brief Construye una nueva instancia de Secante
		* @param strFunc Texto de la funcion
		*/
		secante(string strFunc):f(strFunc){ //Se inicializaron las instancias de la funcion y derivada
		}

		/**
		* @brief Calcula la raiz de la funcion a partir de x0 y x1 dados
		* @param x0 Primer valor
		* @param x1 Segundo valor
		* @param tol Tolerancia (error relativo porcentual)
		* @param n Numero maximo de iteraciones
		* @return Solucion encontrada. La raiz es NAN si no se encuentra la solucion.
		*/
		solucion calcular(double x0, double x1, double tol, int n) {
			solucion sol;

			int & i = sol.iteraciones = 1;

			while (i < n) {


				double x2 = x1 - ((f(x1)*(x0-x1))/(f(x0)-f(x1)));

				//Calcular el error relativo porcentual
				double erp = calcular_erp(x2, x1);

				//Adicionar la aproximacion
				sol.adicionar({x1, x2, erp});

				if ( es_cero(f(x2))  ||
					erp < tol ) {
					//Guardar la raiz
					sol.raiz = x2;
					//TODO sol.iteraciones = i;
					return sol;
				}

				i++;

				//Redefinir el intervalo
				x0 = x1;
				x1 = x2;
			}
			return sol;
		}

	private:
		Expression f; /*!< Evaluador de la funcion */
	};
}

#endif