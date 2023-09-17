#ifndef NEWTON_RAPHSON_H
#define NEWTON_RAPHSON_H

/**
 * @file newton_raphson.h
 * @author Joan Sebastian Tuquerrez Gomez (jtuquerrez@unicauca.edu.co)
 * @brief libreria que implementa el metodo de newton_raphson
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
	* @brief Implementacion del metodo de Newton Raphson
	*/
	class newton_raphson { //El nombre del constructor DEBE ser igual al nombre de la clase
	public:
		/**
		* @brief Construye una nueva instancia de Newton Raphson
		* @param strFunc Texto de la funcion
		* @param strdFun Texto de la derivada de la funcion
		*/
		newton_raphson(string strFunc, string strdFunc):f(strFunc), df(strdFunc) { //Se inicializaron las instancias de la funcion y derivada
		}
		
		/**
		* @brief Calcula la raiz de la funcion a partir de p0
		* @param p0 Aproximacion inicial
		* @param tol Tolerancia (error relativo porcentual)
		* @param n Numero maximo de iteraciones
		* @return Solucion encontrada. La raiz es NAN si no se encuentra la solucion.
		*/
		solucion calcular(double p0, double tol, int n) {
				solucion sol;
				
				//Paso 1
				int & i = sol.iteraciones = 1;
				//Paso 2
				
				/*Validar si el usuario especificifico una raiz
				if (es_cero(f(p0))) {
					//Guardar la raiz
					sol.raiz = p0;
					return sol;
				}*/
			
				//Paso 2
				while (i < n) {
					//Paso 3
					double p = p0 - (f(p0) / df(p0));
					
					//Paso 4
					//Calcular el error relativo porcentual
					double erp = calcular_erp(p, p0);
					
					//Adicionar la aproximacion
					sol.adicionar({p0, p, erp});
					
					if (es_cero(f(p)) ||
						erp < tol ) {
						//Guardar la raiz
						sol.raiz = p;
						return sol;
					}
					//Paso 5
					i++;
					
					//Paso6
					p0 = p;
				}
				
				
				return sol;
		}
	private:
		Expression f; /*!< Evaluador de la funcion */
		Expression df; /*!< Evaluador de la derivada de la funcion */
	};
}

#endif
