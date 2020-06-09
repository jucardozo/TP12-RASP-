/*
main.c - Ejercicio 6
Estas funciones proveen una forma de interaccion con la libreria ports del ejercicio 4 manejando el portA
Creado por el grupo 5
*/

/*HEADERS*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "definitions.h"			//Definiciones generales
#include "ports.h"				//Libreria de puertos
#include "input.h"				//Entrada de datos por teclado
#include "output.h"				//Salida de datos por consola

/*VARIABLES GLOBALES*/
port16_t p;					//Estructura de puertos. Por favor vea "ports.h"
int pulsador=0;
static int Blink(void);			//parpadeo

/*thread*/
void * thread1()
{ int fin=1;
    char keyB;
    while(fin){         //pregunta continuamente si se presiono la tecla B
        keyB=getchar();        
        if(keyB=='B' || keyB=='b'){     //en el caso de que sea la tecla b
            pulsador=0;                 //se baja el flag del pulsador para que el while del Blink pare
             fin=0;                     //se termina el while del thread
        }
	keyB=getchar();		//se saca el buffer basura
    }
    while(1){
    }
}

/*FUNCION PRINCIPAL*/

int main (void){							//Este programa opera sobre el puerto 
	BOOLEAN end = FALSE;					//Variable para terminar el programa
	char in;								//Variable para dar entrada a los datos del usuario
	bienvenida();							//Doy la bienvenida al usuario
	while (end == FALSE){					//Mientras no se quiera finalizar el programa
		in = input();						//Obtengo la entrada
		LINEA_VACIA();
		switch (in){						//Proceso que es lo que se quiere hacer
			case 't': case 'T':				//T o t conmutan todo el puerto
				maskToggle(&p, 'A', 0xFF);		//Como siempre se le pasan datos validos y verificados a las funciones,
				break;						//se ignora el valor que puedan devolver, ya que nunca seria el de un error
			case 'c': case 'C':				//C o c apagan todo el puerto
				maskOff(&p, 'A', 0xFF);
				break;
			case 's': case 'S':				//C o c apagan todo el puerto
				maskOn(&p, 'A', 0xFF);
				break;
			case'B': case'b':
				p.portD.W=Blink();
				break;
			case 'q': case 'Q':				//Q o q finalizan el programa
				printf ("Gracias por utilizar este programa.\n");
				LINEA_VACIA();
				end = TRUE;					//Hacer true a esta variable me da la condicion de salida
				break;
			default:						//Caso de los numeros de 0 a 7
				bitSet (&p, 'A', (((int)in) - ASCII_ZERO));	//Seteo el numero de bit pedido
				break;
		}
		if (end != TRUE){		//Si el usuario no decidio salir
			print_portA(&p);		//Imprimo los cambios del puerto
		}
	}
}	
static int Blink(){         //devuelve la configuracioin inicial de los bits
	int port_original=p.portD.W;                //salva la configuracion inicial
	pthread_t tid1;          //se crea un puntero a un thread
	pthread_create(&tid1,NULL,thread1,NULL);
	pulsador=1;                         //si no se apreto b, entonces el pulsador sigue activo
	while(pulsador){                        //por lo tanto queda atrapado en el while
		sleep(2);
	        maskToggle(&p,'D', p.portD.W);               //apaga los bit que estaban 
	        print_portA(&p);
	        printf("me duermo\n");
	        sleep(2);
	        printf("me despierto\n");
	        maskToggle(&p,'D',port_original);             //prendo de nuevo los bits
	        print_portA(&p);
		sleep(2);
    }
    return port_original;                       //el thread termino.
}