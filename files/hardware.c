/*
hardware.c (Source)
Este archivo contiene todas las funciones que se necesitan para dar salida a los datos utilizando los puertos de la RaspBerry Pi
Creado por el grupo 5
*/

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"



void hard (void){

FILE * handle_direction = NULL;
FILE * handle = NULL;
char led[8]={17,4,18,23,24,25,22,27};
int Written;
int value;

for (unsigned char i=0; i<8; i++){

	if( (handle_direction = PIN_SDIRECT(led[i]) ) == NULL){		//si ocurrio algun error en la direccion del pin devuelvo un 1 
		printf("cannot open DIRECTION File\n");
		exit(1);
	}
 	else {
		printf("DIRECTION File for PIN OPENED succefully\n");	//si no ocurrio ningun error el pin fue abierto satisfactoriamente 
	}
	if ((Written=fputs("out",handle_direction))==-1){
		printf("Cannot open DIRECTION pin. Try again later.\n");
		exit(1);
	}
	else{
		printf("DIRECTION File for PIN opened succesfully\n");
	}

	fflush(handle_direction);

	if ( (handle=PIN_SVALUE(led[i])) == NULL){
		printf("Cannot open device. Try again later.\n");
		exit(1);
	}
	else{
		printf("Device successfully opened\n");
	}

 	if(p.portA_bit.b0 == 1){
		value = 1;
 		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	else {
		value = 0;
		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	if(p.portA_bit.b1 == 1){
		value = 1;
 		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	else {
		value = 0;
		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	if(p.portA_bit.b2 == 1){
		value = 1;
 		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	else {
		value = 0;
		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	if(p.portA_bit.b3== 1){
		value = 1;
 		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	else {
		value = 0;
		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	if(p.portA_bit.b4 == 1){
		value = 1;
 		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	else {
		value = 0;
		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	if(p.portA_bit.b5 == 1){
		value = 1;
 		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	else {
		value = 0;
		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	if(p.portA_bit.b6 == 1){
		value = 1;
 		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	else {
		value = 0;
		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
	
	 	if(p.portA_bit.b7 == 1){
		value = 1;
 		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
 	else {
		value = 0;
		if(PIN_VALUE(value)==-1) {
			printf("Clr_Pin: Cannot write to file. Try again later.\n");
			exit(1);
		}

		else
			printf("Write successfully done.\n");
	}
	fflush(handle);
	
}
	fclose(handle_direction);
	fclose(handle);
}
