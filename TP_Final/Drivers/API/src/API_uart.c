/*
 * API_uart.c
 *
 *  Created on: 21 sep. 2022
 *      Author: MATIAS
 */

#include <string.h>
#include "API_debounce.h"
#include "API_delay.h"
#include "API_uart.h"

/*Se define estructura para configuración de UART*/
UART_HandleTypeDef UartHandle;

/* uartInit:
 * Inicia la comunicación UART.
 * Envía mensaje indicando los parametros de su configuración.
 * Devuelve valor booleano TRUE si la iniciación fue exitosa.*/
bool_t uartInit(void){
	 bool_t successfullInitialization=true;
	 uint8_t baudRateValue[NRO_CARACTERES_CONVERSION]={};
	 uint8_t wordLengthValue[NRO_CARACTERES_CONVERSION]={};
	 uint8_t StopBitsValue[NRO_CARACTERES_CONVERSION]={};

	  /*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART configured as follows:
	      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
		                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	      - Stop Bit    = One Stop bit
	      - Parity      = ODD parity
	      - BaudRate    = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance        = USARTx;

	  UartHandle.Init.BaudRate   = 9600;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_ODD;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&UartHandle) != HAL_OK)
	  {
	    /* Initialization Error */
		successfullInitialization=false;
	    while(1){

	    }

	  }

	  /*Función que convierte valor numérico a char.*/
	  sprintf((char*) baudRateValue, "%d",(int) UartHandle.Init.BaudRate);
	  sprintf((char*) wordLengthValue, "%d",(int) UartHandle.Init.WordLength);
	  sprintf((char*) StopBitsValue, "%d",(int) UartHandle.Init.StopBits);

	  /*Se informa la configuración de los parametros UART.*/
	  uartSendString((uint8_t*)"Uart Iniciada\n\r");
	  uartSendString((uint8_t*)"-----Parametros UART-----\n\r");
	  uartSendString((uint8_t*)"\n\rBaud rate: ");
	  uartSendString((uint8_t*)baudRateValue);
	  uartSendString((uint8_t*)"\n\rWord Length: ");
	  uartSendString((uint8_t*)wordLengthValue);
	  uartSendString((uint8_t*)"\n\rStop Bits: ");
	  uartSendString((uint8_t*)StopBitsValue);
	  uartSendString((uint8_t*)"\n\rParity: Odd");
	  uartSendString((uint8_t*)"\n\r");

	  return successfullInitialization;
}

/* uartSendString:
 * Función que envia un mensaje por UART.
 * Recibe un puntero a array como parametro, el cual contiene el mensaje a enviar.*/
void uartSendString(uint8_t * pstring){
	HAL_UART_Transmit(&UartHandle,(uint8_t*) pstring,strlen((const char*) pstring), TIME_OUT_UART);
}

/* uartSendStringSize:
 * Función que envia un mensaje por UART.
 * Recibe un punto a array como parametro, el cual contiene el mensaje a enviar.
 * Tambien se debe indicar la cantidad de caracteres que deben ser enviados.*/
void uartSendStringSize(uint8_t * pstring, uint16_t size){
	HAL_UART_Transmit(&UartHandle,(uint8_t*) pstring,size, TIME_OUT_UART);
}
