/*
output.h (Header)
Este archivo contiene todas las funciones que se necesitan para dar salida a los datos por consola
Creado por el grupo 5
*/

#ifndef OUTPUT_H
#define OUTPUT_H

/*HEADERS NECESARIOS*/

#include <stdio.h>
#include "definitions.h"
#include "ports.h" 	//Incluyo la libreria de puertos para definir port16_t

/*FUNCIONES*/

void bienvenida (void);				//Doy la bienvenida al usuario
void print_portA (port16_t *);			//Esta funcion imprime el puerto A. Recibe un puntero a la estructura de puertos. No devuelve nada

#endif
