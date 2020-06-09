/*
hardware.h (Header)
Este archivo contiene todas las funciones que se necesitan para dar salida a los datos utilizando los puertos de la RaspBerry Pi
Creado por el grupo 5
*/

#ifndef HARDWARE_H
#define HARDWARE_H
/*DEFINICION DE MACROS*/
#define PIN_SDIRECT(x) fopen(“/sys/class/gpio/gpio##x/direction”,"w")
#define PIN_SVALUE(x) fopen(“/sys/class/gpio/gpio##x/value”,"w")
#define PIN_DIRECT(x) fputc("x",handle_direction)
#define PIN_VALUE(x) fputc('x',handle)
#define VALUE(x) p->portA_bit.b##x

/*DEFINCION DE FUNCIONES*/

void hard (void);

#endif 
