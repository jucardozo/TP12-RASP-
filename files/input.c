/*
input.c (Source)
Este archivo da entrada a los datos mediante el uso de teclado
Creado por el grupo 5
*/

#include "definitions.h"
#include "input.h"

/*PROTOTIPOS DE FUNCIONES INTERNAS*/

static void cleanStdin (void);				//Funcion para limpiar el stdin en caso de una lectura incorrecta
static BOOLEAN is_a_valid_input(char);		//Funcion para verificar si un char es una entrada valida

/*FUNCION EXTERNA*/

char input (void){			//Esta funcion no recibe nada y devuelve un char con el dato que ingreso el usuario por teclado (unico char)
	char c, t;														//Variables temporales
	BOOLEAN valid;													//Variable para evaluar la validez de la entrada
	do{
		valid = TRUE;												//Supongo que la entrada es valida
		c = getchar();												//Obtengo el caracter
		t = getchar();												//Y el terminador
		valid = ((t == '\n') ? valid : FALSE);						//Veo si se obtuvo un terminador
		valid = ((is_a_valid_input(c) == TRUE) ? valid : FALSE);	//Veo si la entrada es valida. Esta funcion puede devolver TRUE o FALSE
		if ((valid == FALSE) && (t != '\n')){						//Si la entrada no es valida porque no se encontro el terminador
			cleanStdin();											//Limpio el stdin
			printf ("Error: ingrese un solo caracter y luego enter.\n");
			LINEA_VACIA();
		}
		else if ((valid == FALSE) && (t == '\n')){					//Si la entrada no es valida pero el terminador si
			printf ("Error: el caracter \"%c\" no es un parametro valido.\n", c);
			LINEA_VACIA();
		}
	}		
	while (valid != TRUE);											//Repito esta operacion siempre que la entrada sea invalida cualquiera sea la razon
	return c;														//Devuelvo el caracter
}

/*FUNCIONES INTERNAS*/

static void cleanStdin (void){		//Funcion para limpiar el stdin
	char c = 0;				//Variable temporal
	while (c != '\n'){		//Obtengo todos los caracteres del stdin hasta el terminador
		c = getchar();
	}
}

static BOOLEAN is_a_valid_input (char c){	//Esta funcion comprueba si el char recibido es valido y devuelve TRUE si lo es o FALSE si no lo es
	BOOLEAN valid = FALSE;					//Supongo que la entrada no es valida
	char valid_letters[10] = {'t', 'T', 'c', 'C', 's', 'S', 'q', 'Q','B','b'};	//Arreglo con las letras de entrada validas
	if ((c >= '0') && (c <= '7')){					//Si el caracter es un numero entre 0 y 7, lo es
		valid = TRUE;
	}
	else{											//Si no es un numero
		for (unsigned int i = 0; i < 10; i++){		//Pero es igual a alguna de las letras del arreglo, valid es TRUE, sino mantiene su valor
			valid = ((c == valid_letters[i]) ? TRUE : valid);
		}											//Al final del for, si no coincidio con ninguna posicion del arreglo, valid es FALSE
	}
	return valid;									//Devuelvo la validez
}
