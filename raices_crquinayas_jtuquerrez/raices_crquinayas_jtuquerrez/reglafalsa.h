#ifndef REGLAFALSA_H
#define REGLAFALSA_H

/**
 * @file reglafalsa.h
 * @author Joan Sebastian Tuquerrez Gomez (jtuquerrez@unicauca.edu.co)
 * @brief libreria que implementa el metodo de la regla falsa
 * @version 1.0.0
 * @date 2023-08-28
 *
 * @copyright Copyright (c) 2023
 */

#include <string>

#include "Expression.h"
#include "solucion.h"

using std::string;

using raices::solucion;
using raices::calcular_erp;

namespace raices {
	/**
	* @brief Raiz de una funcion usando el metodo de la regla falsa
	*/
	class reglafalsa {
	public:
		/**
		* @brief Crear una nueva instancia del metodo de regla falsa
		*/
		reglafalsa(string strFunc):f(strFunc) { //El constructor solo inicializa el evaluador de funciones
		}
		
		solucion calcular(double xi, double xs, double tol, int n) {
			solucion sol;
			
			//Paso 1
			int i = 1;
			//Paso 2
			double xrAnt = xs - ((f(xs)*(xi-xs))/(f(xi)-f(xs)));
			
			//Validar si la primera aproximacion es la raiz
			if ( fabs(f(xrAnt)) <= DBL_EPSILON ) {
				//Guardar la raiz
				sol.raiz = xrAnt;
				return sol;
			}
			
			//Redefinir el intervalo aplicando TVI
			if (f(xi) * f(xrAnt) > 0.0f) {
				xi = xrAnt;
			}else {
				xs = xrAnt;
			}
			
			//Paso 3
			while (i <= n) {
				//Paso 4
				double xrNueva = xs - ((f(xs)*(xi-xs))/(f(xi)-f(xs)));
				//Calcular el error relativo porcentual
				double erp = calcular_erp(xrNueva, xrAnt);
				//Adicionar la aproximacion
				sol.adicionar({xrAnt, xrNueva, erp});
				//Paso 5
				if ( fabs(f(xrNueva)) <= DBL_EPSILON  ||
					erp < tol) {
					//Guardar la raiz
					sol.raiz = xrNueva;
					return sol;
				}
				//Paso 6
				i++;
				//Paso 7
				if (f(xi) * f(xrNueva) > 0.0f) {
					xi = xrNueva;
				}else {
					xs = xrNueva;
				}
				xrAnt = xrNueva;
			}
			
			return sol;
		}	
	private:
		Expression f; /*!< Evaluador de la funcion */
	};
}


#endif
