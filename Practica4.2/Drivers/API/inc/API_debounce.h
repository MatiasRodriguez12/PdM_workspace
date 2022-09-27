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

/*Tiempo empleado para validar una pulsación de boton (en ms)*/
#define TIME_VALID_PUSH 40

/*Prototipos de funciones*/
/*debounceFSM_init
 *Se encarga de asigar el estado inicial en la MEF utilizada para validación de pulsaciones */
void debounceFSM_init(void);

/*debounceFSM_update
 *A partir del estado actual del pulsador, actualiza el estado siguiente de la MEF*/
void debounceFSM_update(void);

/*readKey
 *Función que devuelve un valor booleano TRUE cuando detecte una pulsación válida*/
bool_t readKey(void);



#endif /* API_INC_API_DEBOUNCE_H_ */
