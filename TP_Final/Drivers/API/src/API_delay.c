/*
 * API_delay.c
 *
 *  Created on: 7 sep. 2022
 *      Author: usuario
 */

#include "API_delay.h"

/*DelayInit:
 *Inicializa la estructura para los retardos no bloqueantes.*/
void delayInit( delay_t * delay, tick_t duration ){
	/*Verifica si los parametros introducidos son los adecuados.
	 *Almacena el valor de retardo en el parametro duration. */
	if (delay!=NULL && duration>0 && duration<MAX_DURATION){
		delay->duration=duration;
		delay->running=false;
	}
	else {
	/*En caso de error, enciende LED1 de manera permanente*/
		while(1){
			BSP_LED_On(LED1);
		}
	}
}

/*DelayRead:
 *Función que inicializa la cuenta de tiempo.*/
bool_t delayRead( delay_t * delay ){
	tick_t currentTime;
	bool_t completedTime=false;

	/*Verifica si los parametros introducidos son los adecuados.
	 *Toma una marca de tiempo e inicia la cuenta.
	 *Devuelve un valor booleano TRUE si el tiempo transcurrido es mayor al almacenado en "duration".*/
	if (delay != NULL){
		if (delay->running==false){
			delay->startTime=HAL_GetTick();
			delay->running=true;
			completedTime=false;
		}
		else{
			currentTime=HAL_GetTick();
			if (currentTime - delay->startTime >= delay->duration){
				completedTime=true;
				delay->running=false;
			}
			else{
				completedTime=false;
			}
		}
	}
	else {
		while(1){
	/*En caso de error, enciende LED1 de manera permanente.*/
			BSP_LED_On(LED1);
		}
	}
	return completedTime;
}

/*delayWrite:
 *Función que actualiza el valor de tiempo de retardo.*/
void delayWrite( delay_t * delay, tick_t duration ){
	/*Verifica si los parametros introducidos son los adecuados*/
	if (delay!=NULL && duration>0 && duration<MAX_DURATION){
		delay->duration=duration;
	}
	else {
		while(1){
	/*En caso de error, enciende LED1 de manera permanente.*/
			BSP_LED_On(LED1);
		}
	}
}