/*
ports.c - Source file
Esta libreria se utiliza para el manejo completo de puertos de un microcontrolador
Controla 2 puertos de 8 bits (A y B) y un puerto de 16 bits (D) que es en realidad la union de los anteriores
Creado por el grupo 5 en mayo de 2020
*/

#include "ports.h"

/*PROTOTIPOS DE FUNCIONES INTERNAS*/
static BOOLEAN is_a_valid_port (char port); //Esta funcion comprueba que el identificador de puerto provisto sea valido
static BOOLEAN is_a_valid_bit (char port, int bit);	//Dado un puerto valido, esta funcion comprueba si el numero de bit pedido es valido
static BOOLEAN is_a_valid_mask (char port, int mask); //Dado un puerto y una mascara, esta funcion comprueba si la mascara es adecuada al puerto indicado

/*FUNCIONES EXTERNAS*/

//Funcion para encender un bit. Recibe el puerto y el bit. Devuelve TRUE si hubo un error o FALSE si no lo hubo
//Se recibe un puntero a la estructura de trabajo
BOOLEAN bitSet (port16_t * p, char port, int data){
	BOOLEAN error = FALSE;											//Variable para almacenar si hay error
//VERIFICACION DE ENTRADA	
	if (is_a_valid_port(port) == FALSE){							//Veo si el identificador del puerto es valido
		error = TRUE;												//Si no lo es, hay un error
	}
	else if (is_a_valid_bit(port,data) == FALSE){					//Luego veo si el numero de bit que se provee es un bit valido
		error = TRUE;												//Indico que hubo un error
	}																//Si el puerto no es valido no tiene sentido ver si el bit lo es. Por eso el else if
//OPERACION BITSET
	else{		//Aqui es donde realmente ocurre el seteo pedido. Solo se llega a este caso si los anteriores, que son solo comprobacion, no generaron error
		int offset = 0;												//Genero un offset para la mascara que va a valer 8 para portA y 0 para los otros
		if ((port == 'A') || (port == 'a')){						//Asigno el offset
			offset = PORT_A_OFFSET;
		}
		uint16_t msk = 1;											//Creo una mascara con solo un 1
		msk = msk << (data + offset);								//Shifteo la mascara al bit pedido
		p->portD.W = p->portD.W | msk;								//Y realizo un OR bitwise solo poniendo un uno en el bit que quiero encender
	}
	return error;													//Devuelvo si hubo un error
}																	//POR FAVOR VER LA NOTA AL FINAL DE ESTE ARCHIVO

//Funcion para apagar un bit. Recibe el puerto y el bit. Devuelve TRUE si hubo un error o FALSE si no lo hubo
//Se recibe un puntero a la estructura de trabajo
BOOLEAN bitClear (port16_t * p, char port, int data){
	BOOLEAN error = FALSE;											//Variable para almacenar si hay error
//VERIFICACION DE ENTRADA
	if (is_a_valid_port(port) == FALSE){							//Veo si el identificador del puerto es valido
		error = TRUE;												//Si no lo es, hay un error
	}
	else if (is_a_valid_bit(port,data) == FALSE){					//Luego veo si el numero de bit que se provee es un bit valido
		error = TRUE;												//Indico que hubo un error
	}																//Si el puerto no es valido no tiene sentido ver si el bit lo es. Por eso el else if
//OPERACION BITCLEAR
	else{		//Aqui es donde realmente ocurre el borrado pedido. Solo se llega a este caso si los anteriores, que son solo comprobacion, no generaron error
		int offset = 0;												//Genero un offset para la mascara que va a valer 8 para portA y 0 para los otros
		if ((port == 'A') || (port == 'a')){						//Asigno el offset
			offset = PORT_A_OFFSET;
		}
		uint16_t msk = 1;						//Creo una mascara con todos 0s y un 1 al final
		msk = msk << (data + offset);                                         //Shifteo el 1 al bit deseado
                msk = ~msk;
		p->portD.W = p->portD.W & msk;								//Luego realizo un AND bitwise solo poniendo el cero en el bit que quiero apagar
	}
	return error;													//Devuelvo si hubo un error
}																	//POR FAVOR VER LA NOTA AL FINAL DE ESTE ARCHIVO

//Funcion para conmutar un bit. Recibe el puerto y el bit. Devuelve TRUE si hubo un error o FALSE si no lo hubo
//Se recibe un puntero a la estructura de trabajo
BOOLEAN bitToggle (port16_t * p, char port, int data){
	BOOLEAN error = FALSE;											//Variable para almacenar si hay error
//VERIFICACION DE ENTRADA
	if (is_a_valid_port(port) == FALSE){							//Veo si el identificador del puerto es valido
		error = TRUE;												//Si no lo es, hay un error
	}
	else if (is_a_valid_bit(port,data) == FALSE){					//Luego veo si el numero de bit que se provee es un bit valido
		error = TRUE;												//Indico que hubo un error
	}																//Si el puerto no es valido no tiene sentido ver si el bit lo es. Por eso el else if
//OPERACION BITTOGGLE
	else{		//Aqui es donde realmente ocurre la conmutacion pedida. Solo se llega a este caso si los anteriores, que son solo comprobacion, no generaron error
		int offset = 0;												//Genero un offset para la mascara que va a valer 8 para portA y 0 para los otros
		if ((port == 'A') || (port == 'a')){						//Asigno el offset
			offset = PORT_A_OFFSET;
		}
		uint16_t msk = 1;											//Creo una mascara con solo un 1
		msk = msk << (data + offset);								//Shifteo la mascara al bit pedido
		p->portD.W = p->portD.W ^ msk;								//Y realizo un XOR bitwise conmutando solo el bit pedido
	}	//Para entender esta operacion es util recalcar que la compuerta XOR puede ser vista como un negador controlado de una entrada cuando la otra se pone en 1
	return error;													//Devuelvo si hubo un error
}																	//POR FAVOR VER LA NOTA AL FINAL DE ESTE ARCHIVO

//Funcion para leer un bit. Recibe el puerto y el bit. Devuelve el valor del bit o -1 si hubo un error
//Se recibe un puntero a la estructura de trabajo
int bitGet (port16_t * p, char port, int data){
	int return_value = 0;											//Variable temporal para almacenar el valor que voy a devolver
//VERIFICACION DE ENTRADA	
	if (is_a_valid_port(port) == FALSE){							//Veo si el identificador del puerto es valido
		return_value = -1;											//Si no lo es, hay un error
	}
	else if (is_a_valid_bit(port,data) == FALSE){					//Luego veo si la mascara es correcta, osea, si tiene sentido para la cantidad de bits del puerto
		return_value = -1;											//Indico que hubo un error
	}																//Si el puerto no es valido no tiene sentido ver si la mascara lo es. Por eso el else if
//OPERACION BITGET
	else{		//Aqui es donde se obtiene el bit pedido. Solo se llega a este caso si los anteriores, que son solo comprobacion, no generaron error
		int offset = 0;												//Genero un offset para la mascara que va a valer 8 para portA y 0 para los otros
		if ((port == 'A') || (port == 'a')){						//Asigno el offset
			offset = PORT_A_OFFSET;
		}
		uint16_t aux = p->portD.W;									//Copio el valor del word en una variable auxiliar
		aux = aux >> (data + offset);								//Shifteo la variable auxiliar a la derecha para que el bit pedido quede a en p.b0 (D bit 0)
		if ((aux % 2) == 1){										//Si aux es divisible enteramente por dos, el bit 0 estara en cero y no se ingresa en este if
			return_value = 1;										//Caso contrario, se hace que return_value sea 1. Este es el valor que voy a devolver
		}	
	}
	
	return return_value;											//Devuelvo el valor del bit
}

//Funcion para encender todos los bits en estado alto de una mascara. Recibe el puerto y la mascara. Devuelve TRUE si hubo un error o FALSE si no lo hubo
//Se recibe un puntero a la estructura de trabajo
BOOLEAN maskOn (port16_t * p, char port, int data){
	BOOLEAN error = FALSE;											//Variable para almacenar si hay error
//VERIFICACION DE ENTRADA	
	if (is_a_valid_port(port) == FALSE){							//Veo si el identificador del puerto es valido
		error = TRUE;												//Si no lo es, hay un error
	}
	else if (is_a_valid_mask(port,data) == FALSE){					//Luego veo si la mascara es correcta, osea, si tiene sentido para la cantidad de bits del puerto
		error = TRUE;												//Indico que hubo un error
	}																//Si el puerto no es valido no tiene sentido ver si la mascara lo es. Por eso el else if
//OPERACION MASKON
	else{		//Aqui es donde realmente ocurre el seteo pedido. Solo se llega a este caso si los anteriores, que son solo comprobacion, no generaron error
	uint8_t msk8 = data;	//Transformo la mascara recibida a uint8_t para poder trabajar con los puertos A y B
	uint16_t msk16 = data;	//Transformo la mascara recibida a uint16_t para poder trabajar con el puerto D
		switch (port){
			case 'A': case 'a':
				p->portA_byte.B = p->portA_byte.B | msk8;				//Aplico OR bitwise entre todo el byte del puerto y la mascara
				break;
			case 'B': case 'b':
				p->portB_byte.B = p->portB_byte.B | msk8;				//Aplico OR bitwise entre todo el byte del puerto y la mascara
				break;
			case 'D': case 'd':
				p->portD.W = p->portD.W | msk16;						//Aplico OR bitwise entre todo el word del puerto y la mascara
				break;
			default:
				break;		
		}		
	}
	return error;													//Devuelvo si hubo un error
}

//Funcion para apagar todos los bits en estado alto de una mascara. Recibe el puerto y la mascara. Devuelve TRUE si hubo un error o FALSE si no lo hubo
//Se recibe un puntero a la estructura de trabajo
BOOLEAN maskOff (port16_t * p, char port, int data){
	BOOLEAN error = FALSE;											//Variable para almacenar si hay error
//VERIFICACION DE ENTRADA	
	if (is_a_valid_port(port) == FALSE){							//Veo si el identificador del puerto es valido
		error = TRUE;												//Si no lo es, hay un error
	}
	else if (is_a_valid_mask(port,data) == FALSE){					//Luego veo si la mascara es correcta, osea, si tiene sentido para la cantidad de bits del puerto
		error = TRUE;												//Indico que hubo un error
	}																//Si el puerto no es valido no tiene sentido ver si la mascara lo es. Por eso el else if
//OPERACION MASKOFF
	else{		//Aqui es donde realmente ocurre el borrado pedido. Solo se llega a este caso si los anteriores, que son solo comprobacion, no generaron error
	uint8_t msk8 = data;	//Transformo la mascara recibida a uint8_t para poder trabajar con los puertos A y B
	uint16_t msk16 = data;	//Transformo la mascara recibida a uint16_t para poder trabajar con el puerto D
	msk8 = ~msk8;			//Complemento a 1 la mascara para en lugar de tener todos ceros y los unos en los bits que quiero apagar
	msk16 = ~msk16;			//tenga todos unos y ceros en los bits que quiero apagar. Esto me permite hacer AND bitwise
		switch (port){
			case 'A': case 'a':
				p->portA_byte.B = p->portA_byte.B & msk8;				//Aplico AND bitwise entre todo el byte del puerto y la mascara
				break;
			case 'B': case 'b':
				p->portB_byte.B = p->portB_byte.B & msk8;				//Aplico AND bitwise entre todo el byte del puerto y la mascara
				break;
			case 'D': case 'd':
				p->portD.W = p->portD.W & msk16;						//Aplico AND bitwise entre todo el word del puerto y la mascara
				break;
			default:
				break;		
		}		
	}
	return error;													//Devuelvo si hubo un error
}

//Funcion para conmutar todos los bits en estado alto de una mascara. Recibe el puerto y la mascara. Devuelve TRUE si hubo un error o FALSE si no lo hubo
//Se recibe un puntero a la estructura de trabajo
BOOLEAN maskToggle (port16_t * p, char port, int data){
	BOOLEAN error = FALSE;											//Variable para almacenar si hay error
//VERIFICACION DE ENTRADA	
	if (is_a_valid_port(port) == FALSE){							//Veo si el identificador del puerto es valido
		error = TRUE;												//Si no lo es, hay un error
	}
	else if (is_a_valid_mask(port,data) == FALSE){					//Luego veo si la mascara es correcta, osea, si tiene sentido para la cantidad de bits del puerto
		error = TRUE;												//Indico que hubo un error
	}																//Si el puerto no es valido no tiene sentido ver si la mascara lo es. Por eso el else if
//OPERACION MASKTOGGLE
	else{		//Aqui es donde realmente ocurre la conmutacion pedida. Solo se llega a este caso si los anteriores, que son solo comprobacion, no generaron error
	uint8_t msk8 = data;	//Transformo la mascara recibida a uint8_t para poder trabajar con los puertos A y B
	uint16_t msk16 = data;	//Transformo la mascara recibida a uint16_t para poder trabajar con el puerto D
		switch (port){
			case 'A': case 'a':
				p->portA_byte.B = p->portA_byte.B ^ msk8;				//Aplico XOR bitwise entre todo el byte del puerto y la mascara
				break;
			case 'B': case 'b':
				p->portB_byte.B = p->portB_byte.B ^ msk8;				//Aplico XOR bitwise entre todo el byte del puerto y la mascara
				break;
			case 'D': case 'd':
				p->portD.W = p->portD.W ^ msk16;						//Aplico XOR bitwise entre todo el word del puerto y la mascara
				break;
			default:
				break;		
		}		
	}	//Para entender esta operacion es util recalcar que la compuerta XOR puede ser vista como un negador controlado de una entrada cuando la otra se pone en 1
	return error;													//Devuelvo si hubo un error
}

/*FUNCIONES INTERNAS*/

//Esta funcion verifica si se recibio una letra de puerto correcta recibiendola en un char y devuelve TRUE o FALSE segun lo sea o no
static BOOLEAN is_a_valid_port (char port){
	char valid_ports[6] = {'a', 'A', 'b', 'B', 'd', 'D'};		//Estas son las posibilidades correctas
	BOOLEAN valid = FALSE;						//Comienzo suponiendo que la letra no es valida
	for (unsigned int i = 0; i < 6; i++){		//Y luego para cada posicion del arreglo de letras de puerto validas, veo si coinciden
		valid = ((port == valid_ports[i]) ? TRUE : valid);		//Si el char recibido coincide con alguna posicion del arreglo hago valid = TRUE, y si
	}								//no coincide dejo valid como esta para no perder la validez
	if (valid == FALSE){
		printf ("Error: El caracter %c no es un identificador de puerto valido.\n", port);
	}
	return valid;						//Devuelvo el valor de si la entrada es o no un identificador de puerto valido
}

//Esta funcion verifica si el numero de bit ingresado es valido segun el puerto dado. Recibe un char de identificador de puerto y el numero de bit, y
//devuelve BOOLEAN FALSE si no es valido, o TRUE si lo es
static BOOLEAN is_a_valid_bit (char port, int bit){
	BOOLEAN valid;				//Variable para evaluar la validez
	int maxbits;				//Variable que contendra el maximo de bits permitidos para el puerto
	switch(port){
		case 'A': case 'a':
		case 'B': case 'b':
			maxbits = PORT_AB_MSb;	//Los puertos A y B son de 8 bits (numerados de 0 a 7)
			break;
		case 'D': case 'd':
			maxbits = PORT_D_MSb;	//El puerto D es de 16 bits (numerados de 0 a 15)
			break;
		default:
			break;				//Caso por defecto (nunca se deberia utilizar)
	}
	valid = ((bit <= maxbits) ? TRUE : FALSE);		//Verifico que el numero de bit sea menor o igual a maxbits. Valid es FALSE si esto no se cumple
	if (valid == FALSE){
		printf ("Error: El numero de bit excede el maximo permitido para el puerto especificado (%d).\n", maxbits);
	}
	if (bit < 0){				//Por ultimo, si el numero de bit es negativo, esto es un error
		printf ("El numero de bit no puede ser negativo.\n");
		valid = FALSE;			//Y se fuerza valid a ser FALSE
	}
	return valid;				//Devuelvo la validez
}

//Esta funcion si la mascara recibida en data es valida o no segun el puerto dado. Recibe, ademas de la mascara en un int, un identificador de puerto ya validado
//en forma de un char. Devuelve BOOLEAN FALSE si no es valido, o TRUE si lo es
static BOOLEAN is_a_valid_mask (char port, int mask){
	BOOLEAN valid;				//Variable para evaluar la validez
	int maxmask;				//Variable que contendra el maximo valor de la mascara permitido para el puerto
	int maxbits;				//Variable que contendra el maximo de bits permitidos para el puerto
	switch(port){
		case 'A': case 'a':
		case 'B': case 'b':
			maxmask = PORT_AB_MAX_MSK;		//Los puertos A y B son de 8 bits y la mascara mas grande que ocupa 8 bits es 0xFF
			maxbits = PORT_AB_BITS;		//Numero de bits que tienen los puertos A y B
			break;
		case 'D': case 'd':
			maxmask = PORT_D_MAX_MSK;	//El puerto D es de 16 bits y la mascara mas grande que ocupa 16 bits es 0xFFFF
			maxbits = PORT_D_BITS;		//Numero de bits que tiene el puerto D
			break;
		default:
			break;				//Caso por defecto (nunca se deberia utilizar)
	}
	valid = ((mask <= maxmask) ? TRUE : FALSE);		//Verifico que la mascara sea menor o igual que maxmask. Valid es FALSE si esto no se cumple
	if (valid == FALSE){
		printf ("Error: La mascara ingresada excede el maximo de bits permitido para el puerto especificado (%d bits).\n", maxbits);
		printf ("Nota: La mascara mas grande que puede definir para el puerto %c es 0x%X.\n", port, maxmask);
	}
	if (mask < 0){				//Por ultimo, si la mascara es negativa, esto es un error
		printf ("La mascara no puede ser negativa.\n");
		valid = FALSE;			//Y se fuerza valid a ser FALSE
	}
	return valid;				//Devuelvo la validez
}

/*NOTA IMPORTANTE PARA EL PROFESOR:
Es verdad, la forma en la que el struct esta definido incluye operaciones bit a bit, haciendo p.bX, o p.portD_[low/high]_bit.bX, o directamente
p.port[A/B]_bit.bX; pero la razon real por la cual hacemos operaciones bit a bit utilizando mascaras y no utilizando todo el potencial que el struct que
definimos ofrece, es por eficiencia y tamaño del codigo. Si bien en un programa para correr en un compilador es necesario hacer funciones que verifiquen
que la entrada que dio el usuario sea correcta, cosa que si tuvieramos que correr el programa en un microcontrolador probablemente no se necesitaria en
ciertos casos, ya que la entrada es mas limitada; lo que no se puede suprimir a la hora de cargar el programa en un microcontrolador real son las funciones
que hacen que el programa haga lo pedido, y la eficiencia del codigo al correrlo en un microcontrolador, donde los recursos son limitados, es importante.
Como las macros se resuelven en tiempo de compilacion, no es posible crear una macro parametrizada que se le de como entrada el numero de bit deseado y que
"construya" la linea de codigo necesaria para operarlo, por lo que hay dos posibles soluciones para el problema de poder operar sobre cada uno de los 16 bits
del puerto D y sobre cada uno de los 8 bits de los puertos A y B:
1_ Escribir switches con 32 case en total anidados dentro de condicionales if, else if y else; lo que genera muchisimas operaciones de branch a nivel assembly,
y hace que el codigo sea larguisimo y terriblemente ineficiente. Pro: se podria utilizar todo el poder del struct definido
2_ Minimizar las decisiones que el microcontrolador debe tomar, mejorando la eficiencia y el uso de memoria, utilizando operaciones bitwise.
Contra: se utiliza poco de todo el poder del struct definido.
Basado en esto, y dado que el target que supone el ejercicio es un microcontrolador, priorizamos eficiencia frente a la simpleza de poner muchos switch case
y encender o apagar bits utilizando las operaciones que provee el struct.
Ahora bien, cabe preguntarse, "por que definieron un struct con tantas formas de utilizacion para usar una o dos? Porque al ser una libreria 
quisimos que sea facilmente actualizable con nuevas funciones, nuevos usos. Esta modularidad tiene muchisimo sentido al
considerar que queremos hacer una libreria para manejo de puertos en lugar de un simple programa que haga algo puntual. Pensando en esto, si quisieramos implementar
una nueva funcion especifica que haga uso de ciertos bytes, bits, o partes puntuales de un puerto, hacer una mascara es, como poco, engorroso. Es por esto que
decidimos ofrecer mas soporte a la hora de crear nuevas funciones para esta libreria, poniendo a disposicion herramientas para cualquier desarrollo.
Si, es verdad, es un TP, no el firmware de un microcontrolador para un proyecto que debe ser mantenido, pero si el struct definido ocupa la misma memoria que un
bitfield de 16 members, por que no agregar mas usos que idealmente le den soporte a cualquier desarrollo?
*/
