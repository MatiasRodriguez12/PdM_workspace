/*
 * API_delay.h
 *
 *  Created on: 7 sep. 2022
 *      Author: usuario
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/*Tiempos de toggle de cada led (en ms)*/
#define TIME_VALID_PUSH 40
/*Tiempo maximo permitido para encender/apagar un led ((en ms))*/
#define MAX_DURATION 30000
/*Estado actual de cada led:*/
/*Estado actual apagado*/
#define ESTADO_OFF 0
/*Estado actual encendido*/
#define ESTADO_ON 1

/*Declaracion de estructura y tipos de variables*/
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

/*Prototipos de funciones*/

/*delayInit
  Se encarga de inicializar el valor de toggle de led. No inicializa el contador.

  Parametros:
  Puntero a memoria delay.
  Tiempo de duracion de toggle de led*/
void delayInit( delay_t * delay, tick_t duration );

/*delayRead
  Se encarga de inicializar el contador.
  En primer lugar toma una marca de tiempo, luego la cual (en cada llamado)
  se compara con el tiempo actual.
  Si la diferencia entre el tiempo actual y la marca de tiempo es mayor a la duracion prefijada,
  devuelve un valor booleano TRUE.

  Parametros:
  Puntero a memoria delay.*/
bool_t delayRead( delay_t * delay );

/*delayWrite
  Se encarga de actualizar el valor de toggle de led.

  Parametros:
  Puntero a memoria delay.
  Tiempo de duracion de toggle de led*/
void delayWrite( delay_t * delay, tick_t duration );



#endif /* API_INC_API_DELAY_H_ */
