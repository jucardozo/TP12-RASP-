/*
ports.h - Header file
Esta libreria se utiliza para el manejo completo de puertos de un microcontrolador
Controla 2 puertos de 8 bits (A y B) y un puerto de 16 bits (D) que es en realidad la union de los anteriores
Creado por el grupo 5 en mayo de 2020
*/

#ifndef PORTS_H
#define PORTS_H

/*HEADERS NECESARIOS*/

#include <stdio.h>
#include <stdint.h>

/*MACROS DE TIPO DE DATO PERSONALIZADO*/

#define BOOLEAN int
#define TRUE 1
#define	FALSE 0

/*MACROS DE VALORES DE PUERTOS*/

#define PORT_AB_BITS 8
#define PORT_D_BITS 16
#define PORT_AB_MSb 7
#define PORT_D_MSb 15
#define PORT_AB_MAX_MSK 0xFF
#define PORT_D_MAX_MSK 0xFFFF
#define PORT_A_OFFSET 8

/*ESTRUCTURAS*/

//Estructura bit a bit para puerto de 8 bits (generica)
typedef struct{
	uint8_t b0 :1; 
	uint8_t b1 :1;
	uint8_t b2 :1;
	uint8_t b3 :1;
	uint8_t b4 :1;
	uint8_t b5 :1;
	uint8_t b6 :1;
	uint8_t b7 :1;
}port8_bit_t;

//Estructura de byte para puerto de 8 bits (generica)
typedef struct{
	uint8_t B;
}port8_byte_t;

//Estructura para offset que sirve para la union en partes altas
typedef struct{
    uint8_t unused_offset_byte;
}unused_byte_t;

//Unica estructura de puertos con alias portD (word, byte y bitfield)
typedef struct{
    union{
        union{
            uint16_t W;			        //Acceso a portD a nivel word (uso: p.portD.W) (se pone este union para hace mas intuitivo el acceso
	}portD;							//al word. Es para que quede p.portD.W que se asemeja a la estructura de byte, y no p.portD_W
        union{
            port8_byte_t portD_low_byte;//Acceso a portD parte baja a nivel byte (uso: p.portD_low_byte.B)
            port8_bit_t portD_low_bit;	//Acceso a portD parte baja a nivel bit (uso: p.portD_low_bit.bX donde X es un numero entero entre 0 y 7)
            struct{
    		    uint8_t b0 :1; 
        	    uint8_t b1 :1;				//Acceso a portD completo (parte alta y baja) a nivel bit.
        	    uint8_t b2 :1;				//Uso: p.bX donde X es un numero entero entre 0 y 15 escrito con una sola cifra en
        	    uint8_t b3 :1;				//caso de los numeros entre 0 y 9
           	    uint8_t b4 :1;
        	    uint8_t b5 :1;
        	    uint8_t b6 :1;
        	    uint8_t b7 :1;
            };
    	};
    	struct{
    	    unused_byte_t unused_offset_byte0;	//Offset de 1 byte para acomodar parte alta
    	    union{
        	    port8_byte_t portD_high_byte;//Acceso a portD parte alta a nivel byte (uso: p.portD_high_byte.B)
        	    port8_bit_t portD_high_bit;	//Acceso a portD parte alta a nivel bit (uso: p.portD_high_bit.bX donde X es un numero entero entre 0 y 7)
        	    struct{
        		uint8_t b8 :1; 
        		uint8_t b9 :1;
       			uint8_t b10 :1;
             	  	uint8_t b11 :1;
                    	uint8_t b12 :1;
              	    	uint8_t b13 :1;
	                uint8_t b14 :1;
                	uint8_t b15 :1;
        	    };
    	    };
        };
		union{							//Acceso a portB (portD parte baja)
			port8_byte_t portB_byte;	//Acceso a nivel byte (uso: p.portB_byte.B)
    		port8_bit_t portB_bit;		//Acceso a nivel bit (uso: p.portB_bit.bX) con X entre 0 y 7
		};
		struct{
			unused_byte_t unused_offset_byte1;	//Offset de 1 byte para acomodar parte alta
			union{								//Acceso a portA (portD parte alta)
				port8_byte_t portA_byte;		//Acceso a nivel byte (uso: p.portA_byte.B)
				port8_bit_t portA_bit;			//Acceso a nivel bit (uso: p.portA_bit.bX) con X entre 0 y 7
			};
		};
    };
}port16_t;

/*Si bien esta estructura es algo compleja, tiene su razon de ser. No solo permite acceder bit a bit y por byte al portA, portB,
y a la totalidad llamandola portD, sino que si se deseara realizar una operacion con un puerto de 16 bits (portD) donde ni portA
ni portB tienen nada que ver, de esta forma se puede hacerlo, logrando independizar los conceptos de portA y portB de portD para
un uso mas intuitivo. Ademas se permite el manejo de a bytes o bit a bit del portD, el manejo bit a bit de las partes alta y baja de
portD por separado (otra vez, separandolo del concepto de manejo bit a bit de portA y de portB, aunque a nivel operacion sea lo mismo),
y tambien, por supuesto, permite el manejo de portD a nivel de word. Todos los usos estan aclarados en los comentarios que indican que
hace cada linea y como usarla. Lo que se busca con esta estructura es una mejora en la claridad de las funciones que la utilicen.*/

/*			RESUMEN USAGE:
p->portD.W					//PortD word
p->portD_[low/high]_byte.B			//PortD byte
p->portD_[low/high]_bit.bX, x en [0,7]		//PortD byte -> bit
p->bX ,x en [0,15]				//PortD bit
p->port[A/B]_byte.B				//PortA/PortB byte
p->port[A/B]_bit.bX, x en [0,7]			//PortA/Portb bit
*/

/*FUNCIONES*/

//Todas las funciones reciben un char con el identificador de puerto, y un int con el numero de bit o la mascara segun corresponda
//Todas las funciones (excepto bitGet) devuelven TRUE si hubo un error, o FALSE si no hubo errores
BOOLEAN bitSet (port16_t *, char port, int data); //Setea (pone en 1) un bit de un puerto determinado
BOOLEAN bitClear (port16_t *, char port, int data);		//Limpia (pone en 0) un bit de un puerto determinado
BOOLEAN bitToggle (port16_t *, char port, int data);	//Conmuta el valor de un bit de un puerto determinado
int bitGet (port16_t *, char port, int data);			//Obtiene el valor de un bit. Devuelve dicho valor si no hubo errores, o -1 si hubo un error
BOOLEAN maskOn (port16_t *, char port, int data);		//Enciende todos los bits de un puerto segun los bits seteados de una mascara
BOOLEAN maskOff (port16_t *, char port, int data);		//Apaga todos los bits de un puerto segun los bits seteados de una mascara
BOOLEAN maskToggle (port16_t *, char port, int data);	//Conmuta todos los bits de un puerto segun los bits seteados de una mascara

#endif
