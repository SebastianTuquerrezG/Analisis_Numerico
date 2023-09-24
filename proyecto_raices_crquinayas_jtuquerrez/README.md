# Elaborado por:
- Cristian David Quinayas Rivera <crquinayas@unicauca.edu.co>
- Joan Sebastian Tuquerrez Gomez <jtuquerrez@unicauca.edu.co>

# Proyecto de Métodos Numéricos

Este proyecto tiene como objetivo implementar y comparar diferentes métodos numéricos para encontrar raíces de ecuaciones no lineales de una variable. Se utilizará la librería `Expression.h` en C para evaluar y manipular ecuaciones.

## Métodos Implementados

1. **Bisección**: El método de la bisección divide repetidamente un intervalo en dos partes y selecciona el subintervalo que sigue cumpliendo con el Teorema del Valor Intermedio.

2. **Regla Falsa**: El método de la regla falsa utiliza interpolación lineal para encontrar la raíz de la ecuación en un intervalo dado.

3. **Secante**: El método de la secante aproxima la raíz de la ecuación mediante una recta secante a la curva de la función.

4. **Newton-Raphson**: El método de Newton-Raphson utiliza la derivada de la función para encontrar una aproximación de la raíz.

5. **Newton-Raphson Generalizado**: Similar al método de Newton-Raphson, pero aplicado a sistemas de ecuaciones en varias variables.

6. **Müller**: El método de Müller utiliza interpolación cuadrática para aproximar la raíz de la ecuación utilizando tres puntos cercanos.

## Uso de la Librería `expression`

La librería `expression` en C permite crear, evaluar y manipular expresiones matemáticas de una manera conveniente. Se utiliza para definir las funciones y ecuaciones necesarias en los programas que implementan los métodos numéricos.

## Ejecución de los Programas

Para ejecutar los programas que implementan los métodos numéricos, sigue estos pasos:

1. Clona este repositorio a tu máquina local.

2. Proporciona la ecuación o funcion en el vectorFunciones, en el archivo main.cpp, seguido de su primera derivada y su segunda derivada.

3. Ejecuta el programa main.cpp.

4. Aparecera un menu para escoger el metodo a utilizar, seleccionar uno.

5. Seguido aparecera el listado de funciones disponibles para hallar la raiz, seleccionar una.

6. Ingresar las aproximaciones requeridas segun el metodo seleccionado y la cantidad de iteraciones.

## Resultados y Comparaciones

En este proyecto, se compararán los resultados y el rendimiento de los diferentes métodos numéricos en la búsqueda de raíces de ecuaciones de una variable. Se analizarán factores como la convergencia, la precisión y el número de iteraciones necesarias.

## Contribuciones

Queremos agradecer al autor de la librería `Expressions.h` por proporcionar una herramienta valiosa que ha hecho posible este proyecto.
Erwin Meza Vega <emezav@unicauca.edu.co>

## Licencia

Este proyecto se encuentra bajo la Licencia GNU 3.0. Puedes consultar el archivo `LICENSE` para más detalles.

