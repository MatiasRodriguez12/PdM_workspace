/*
 * API_debounce.h
 *
 *  Created on: 14 sep. 2022
 *      Author: MATIAS
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "API_delay.h"

//Declaración de estructura para estados de MEF
typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t;

/*Tiempo empleado para validar una pulsación de boton (en ms)*/
#define TIME_VALID_PUSH 40

#define PULSADOR_UP 0
#define PULSADOR_DOWN 1

/*Prototipos de funciones*/
/*debounceFSM_init
 *Se encarga de asigar el estado inicial en la MEF utilizada para validación de pulsaciones */
void debounceFSM_init(void);

/*debounceFSM_update
 *A partir del estado actual del pulsador, actualiza el estado siguiente de la MEF.
 *Se le debe indicar (por parametro de entrada) cual es el pulsador a analizar.
 *
 *Parametro: PULSADOR_UP/PULSADOR_DOWN*/
void debounceFSM_update(uint8_t pulsador);

/*readKeyUP
 *Función que devuelve un valor booleano TRUE cuando detecte una pulsación válida de button UP*/
bool_t readKeyUP(void);

/*readKeyDOWN
 *Función que devuelve un valor booleano TRUE cuando detecte una pulsación válida de button DOWN*/
bool_t readKeyDOWN(void);


#endif /* API_INC_API_DEBOUNCE_H_ */
