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
#include "API_delay.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

#define nroCaracteresConversion 5
#define timeOutUart 0xFFFF

//PARA HACER FUNCIONAR, EN ARCHIVO stm32f4xx_hal_msp.c INCLUI API_uart.h

/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3

/* uartInit:
 * Inicia la comunicación UART.
 * Envía mensaje indicando los parametros de su configuración.
 * Devuelve valor booleano TRUE si la iniciación fue exitosa.*/
bool_t uartInit(void);

/* uartSendString:
 * Función que envia un mensaje por UART.
 * Recibe un puntero a array como parametro, el cual contiene el mensaje a enviar.
 *
 * Parametro: string que contiene el mensaje a enviar.*/
void uartSendString(uint8_t * pstring);

/* uartSendStringSize:
 * Función que envia un mensaje por UART.
 * Recibe un punto a array como parametro, el cual contiene el mensaje a enviar.
 * Tambien se debe indicar la cantidad de caracteres que deben ser enviados.
 *
 * Parametros: string que contiene el mensaje a enviar.
 * 			   cantidad de caracteres a enviar.*/
void uartSendStringSize(uint8_t * pstring, uint16_t size);

/* uartReceiveStringSize:
 * Función utilizada para la recepción de mensajes por UART.
 * Esta función no esta desarrollada en este proyecto.
 *
 * Parametros: String donde se va a almacenar la palabra recibida.
 * 			   Cantidad de caracteres a almacenar.*/
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */
