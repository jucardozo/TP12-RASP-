/*
output.c (Source)
Este archivo contiene todas las funciones que se necesitan para dar salida a los datos por consola
Creado por el grupo 5
*/

#include "output.h"

void bienvenida (void){						//Esta funcion da la bienvenida al usuario. No recibe ni devuelve nada
	printf ("Grupo 5.\n");
	printf ("Este programa simula LEDs conectados al puerto A utilizando la libreria \"ports\".\n");
	printf ("Un espacio vacio ( ) es un LED apagado, y uno relleno (*) es un LED encendido.\n");
	printf ("Todos los bits inician apagados.\n");
	printf ("Por favor ingrese:\n");
	printf ("	* Un numero entre 0 y 7 para encender ese bit.\n");
	printf ("	* \"T\" o \"t\" para conmutar el estado de todos los LEDs.\n");
	printf ("	* \"C\" o \"c\" para apagar todos los LEDs.\n");
	printf ("	* \"S\" o \"s\" para encender todos los LEDs.\n");
	printf ("	* \"Q\" o \"q\" para salir del programa.\n");
	LINEA_VACIA();
}

void print_portA (port16_t * p){	//Esta funcion imprime el puerto A. Recibe un puntero a la estructura de puertos. No devuelve nada
	char tmp[8];					//Variable temporal
	for (unsigned int i = 0; i <= 7; i++){		//Para cada posicion del arreglo
		switch (i){
			case 0:				//Si el bit correspondiente a esa posicion es cero
				if ((p->b8)==0)		//Cuidado: el portA inicia en el bit 8, no en el 0
					tmp[0] = ' ';	//Guardo en el arreglo un espacio
				else
					tmp[0] = '*';	//Y si es uno guardo un asterisco
				break;
			case 1:				//Y asi con todos los bits
				if ((p->b9)==0)
					tmp[1] = ' ';
				else
					tmp[1] = '*';
				break;
			case 2:
				if ((p->b10)==0)
					tmp[2] = ' ';
				else
					tmp[2] = '*';
				break;
			case 3:
				if ((p->b11)==0)
					tmp[3] = ' ';
				else
					tmp[3] = '*';
				break;
			case 4:
				if ((p->b12)==0)
					tmp[4] = ' ';
				else
					tmp[4] = '*';
				break;
			case 5:
				if ((p->b13)==0)
					tmp[5] = ' ';
				else
					tmp[5] = '*';
				break;
			case 6:
				if ((p->b14)==0)
					tmp[6] = ' ';
				else
					tmp[6] = '*';
				break;
			case 7:
				if ((p->b15)==0)
					tmp[7] = ' ';
				else
					tmp[7] = '*';
				break;
			default:
				printf ("Error interno: main.c > print_portA > for > switch > default\n");	//Nunca deberia suceder
				break;
		}
	}
	printf (" %c %c %c %c %c %c %c %c \n",tmp[7],tmp[6],tmp[5],tmp[4],tmp[3],tmp[2],tmp[1],tmp[0]);		//Imprime los leds (espacios o asteriscos)
	printf (" 7 6 5 4 3 2 1 0 \n");				//Numero de bit. Decorativo
	LINEA_VACIA();
	printf ("Hexadecimal: 0x%X\n",p->portA_byte.B);		//Imprimo tambien el valor en hexadecimal
	LINEA_VACIA();
}
