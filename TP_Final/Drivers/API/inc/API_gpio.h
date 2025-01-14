/*
 * API_gpio.h
 *
 *  Created on: 26 sep. 2022
 *      Author: MATIAS
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

#include <stdint.h>
#include "main.h"
#include "API_delay.h"

/*DEFINICIONES DE PUERTOS Y PINES PARA TERMINALES DE D0 A D6*/
#define D0_PORT 	GPIOG
#define D0_PIN  	GPIO_PIN_9
#define D1_PORT 	GPIOG
#define D1_PIN  	GPIO_PIN_14
#define D2_PORT 	GPIOF
#define D2_PIN  	GPIO_PIN_15
#define D3_PORT 	GPIOE
#define D3_PIN  	GPIO_PIN_13
#define D4_PORT 	GPIOF
#define D4_PIN  	GPIO_PIN_14
#define D5_PORT		GPIOE
#define D5_PIN  	GPIO_PIN_11
#define D6_PORT 	GPIOE
#define D6_PIN	  	GPIO_PIN_9
#define D15_PORT	GPIOB
#define D15_PIN  	GPIO_PIN_8

/*CANTIDAD DE LEDS QUE POSEE EL DISPLAY*/
#define NUMERO_LEDS_DISPLAY 7

/*MASCARA USADA PARA SEPARAR BITS*/
#define MASCARA_SEPARA_BITS 0x01

/*Estados posibles de los puertos D0 a D6*/
typedef enum{
	LOW,
	HIGH
} gpio_state;

/*gpioDisplay_init:
 *Configura los puertos D0 a D6 como salidas.*/
void gpioDisplay_init(void);

/*gpioButton_init:
 *Configura el puerto D15 como entrada.*/
void gpioButton_init(void);

/*gpioButton_Read:
 *Función que devuelve el estado del interruptor externo (conectado en D15).*/
bool_t gpioButton_Read(void);

/*gpioDisplay_write:
 *Actualiza el estado de los puertos D0 a D6, generando la representación de números en el display.
 *
 *Parametro: Array de estado de puertos GPIO.*/
void gpioDisplay_write(uint8_t valorDisplay);

#endif /* API_INC_API_GPIO_H_ */
