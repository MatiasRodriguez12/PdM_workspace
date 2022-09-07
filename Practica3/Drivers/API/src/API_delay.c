/*
 * API_delay.c
 *
 *  Created on: 7 sep. 2022
 *      Author: usuario
 */

#include <API_delay.h>

/*Defino las funciones*/
void delayInit( delay_t * delay, tick_t duration ){
	//Verifica si los parametros introducidos son los adecuados
	if (delay!=NULL && duration>0 && duration<MAX_DURATION){
		delay->duration=duration;
		delay->running=false;
	}
	else {
	//En caso de error, enciende LED1 de manera permanente
		while(1){
			BSP_LED_On(LED1);
		}
	}
}

bool_t delayRead( delay_t * delay ){
	tick_t currentTime;
	bool_t toggleLED=false;

	//Verifica si los parametros introducidos son los adecuados
	if (delay != NULL){
		if (delay->running==false){
			delay->startTime=HAL_GetTick();
			delay->running=true;
			toggleLED=false;
		}
		else{
			currentTime=HAL_GetTick();
			if (currentTime - delay->startTime >= delay->duration){
				toggleLED=true;
				delay->running=false;
			}
			else{
				toggleLED=false;
			}
		}
	}
	return toggleLED;
}

void delayWrite( delay_t * delay, tick_t duration ){
	//Verifica si los parametros introducidos son los adecuados
	if (delay!=NULL && duration>0 && duration<MAX_DURATION){
		delay->duration=duration;
	}
	else {
		while(1){
	//En caso de error, enciende LED1 de manera permanente
			BSP_LED_On(LED1);
		}
	}
}
