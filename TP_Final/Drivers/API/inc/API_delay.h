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
#include <stdbool.h>
#include <stdint.h>
#include "main.h"

/*Tiempo maximo permitido para establecer un retardo ((en ms))*/
#define MAX_DURATION 30000

/*Declaracion de estructura y tipos de variables para retardos no bloqueantes.*/
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

/*Prototipos de funciones*/

/*delayInit:
  Inicializa la estructura para los retardos no bloqueantes.
  No inicializa el contador.

  Parametros:
  Puntero a memoria delay.
  Tiempo de duracion de retardo*/
void delayInit( delay_t * delay, tick_t duration );

/*delayRead:
  Se encarga de inicializar el contador.
  En primer lugar toma una marca de tiempo, luego la cual (en cada llamado)
  se compara con el tiempo actual.
  Si la diferencia entre el tiempo actual y la marca de tiempo es mayor a la duracion prefijada,
  devuelve un valor booleano TRUE.

  Parametros:
  Puntero a memoria delay.*/
bool_t delayRead( delay_t * delay );

/*delayWrite:
  Se encarga de actualizar el valor de retardo.

  Parametros:
  Puntero a memoria delay.
  Tiempo de duracion de retardo*/
void delayWrite( delay_t * delay, tick_t duration );



#endif /* API_INC_API_DELAY_H_ */
