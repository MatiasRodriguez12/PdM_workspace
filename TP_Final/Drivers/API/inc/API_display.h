/*
 * API_display.h
 *
 *  Created on: 27 sep. 2022
 *      Author: MATIAS
 */

#ifndef API_INC_API_DISPLAY_H_
#define API_INC_API_DISPLAY_H_

#include <stdint.h>

/*Constante utilizada para realizar la conversión del número del estado actual de la MEF a caracter y enviarlo por UART.
 *Se requieren 2 caracteres, el número propiamente dicho y el caracter nulo.*/
#define NRO_CARACTERES_ESTADO 2

/*Se representa como un array de 7 bits los estados en que se
 *deben encontrar los puertos (D6 a D0) para poder representar los numeros de 0 a 9 en el display.
 *		1: Puerto en HIGH.
 *		0: Puerto en LOW.
 *A continuaciÓn se muestra el valor correspondiente de dicho array, expresado en base decimal.
 *					  Led display:  b -  a -  f -  g -  c -  d  - e
 *							pines: D6 - D5 - D4 - D3 - D2 - D1 - D0*/
#define NRO_CERO 	119			//  1 -  1 -  1 -  0 -  1 -  1 -  1
#define NRO_UNO		68			//  1 -  0 -  0 -  0 -  1 -  0 -  0
#define NRO_DOS		107			//  1 -  1 -  0 -  1 -  0 -  1 -  1
#define NRO_TRES	110			//  1 -  1 -  0 -  1 -  1 -  1 -  0
#define NRO_CUATRO 	92			//  1 -  0 -  1 -  1 -  1 -  0 -  0
#define NRO_CINCO 	62			//  0 -  1 -  1 -  1 -  1 -  1 -  0
#define NRO_SEIS 	63			//  0 -  1 -  1 -  1 -  1 -  1 -  1
#define NRO_SIETE 	100			//  1 -  1 -  0 -  0 -  1 -  0 -  0
#define NRO_OCHO 	127			//  1 -  1 -  1 -  1 -  1 -  1 -  1
#define NRO_NUEVE 	124			//  1 -  1 -  1 -  1 -  1 -  0 -  0

/*Se definen los estados de la MEF del display.*/
typedef enum{
State_0,
State_1,
State_2,
State_3,
State_4,
State_5,
State_6,
State_7,
State_8,
State_9,
} displayState_t;

/*displayFSM_init.
 *Función que inicializa la MEF de display.*/
void displayFSM_init(void);

/*displayFSM_update.
 *Función que actualiza el estado de la MEF de display.*/
void displayFSM_update(void);

/*getStateDisplay.
 *Función que devuelve el array de estado de los puertos GPIO, según el estado actual de la MEF de display.*/
uint8_t getStateDisplay(void);

#endif /* API_INC_API_DISPLAY_H_ */
