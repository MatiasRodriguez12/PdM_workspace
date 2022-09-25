/*
 * API_uart.h
 *
 *  Created on: 21 sep. 2022
 *      Author: MATIAS
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <API_delay.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

/* Inicia la comunicación UART.
 * Envía mensaje indicando los parametros de su configuración.
 * Devuelve valor booleano TRUE si la iniciación fue exitosa.*/
bool_t uartInit(void);

/* Función que envia un mensaje por UART.
 * Recibe un punto a array como parametro, el cual contiene el mensaje a enviar.*/
void uartSendString(uint8_t * pstring);

/* Función que envia un mensaje por UART.
 * Recibe un punto a array como parametro, el cual contiene el mensaje a enviar.
 * Tambien se debe indicar la cantidad de caracteres que deben ser enviados.*/
void uartSendStringSize(uint8_t * pstring, uint16_t size);

/* Función utilizada para la recepción de mensajes por UART.
 * Esta función no esta desarrollada en este proyecto.*/
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */
