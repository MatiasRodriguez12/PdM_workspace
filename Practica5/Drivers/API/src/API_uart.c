/*
 * API_uart.c
 *
 *  Created on: 21 sep. 2022
 *      Author: MATIAS
 */

#include "API_debounce.h"
#include "API_delay.h"
#include "API_uart.h"
#include <string.h>
#include "main.h"

UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}


/* Inicia la comunicación UART.
 * Envía mensaje indicando los parametros de su configuración.
 * Devuelve valor booleano TRUE si la iniciación fue exitosa.*/
bool_t uartInit(void){
	 bool_t successfulInitialization=true;
	 char baudRateValue[5]={};
	 char wordLengthValue[5]={};
	 char StopBitsValue[5]={};
	 char parityValue[5]={};

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
		successfulInitialization=false;
	    while(1){

	    }

	  }

	  //Funcion que convierte valor numerico a char
	  sprintf((char*) baudRateValue, "%d",(int) UartHandle.Init.BaudRate);
	  sprintf((char*) wordLengthValue, "%d",(int) UartHandle.Init.WordLength);
	  sprintf((char*) StopBitsValue, "%d",(int) UartHandle.Init.StopBits);
	  sprintf((char*) parityValue, "%d",(int) UartHandle.Init.Parity);

	  uartSendString((uint8_t*)"Uart Iniciada\n\r");
	  uartSendString((uint8_t*)"-----Parametros UART-----\n\r");
	  uartSendString((uint8_t*)"\n\rBaud rate: ");
	  uartSendString((uint8_t*)baudRateValue);
	  uartSendString((uint8_t*)"\n\rWord Length: ");
	  uartSendString((uint8_t*)wordLengthValue);
	  uartSendString((uint8_t*)"\n\rStop Bits: ");
	  uartSendString((uint8_t*)StopBitsValue);
	  uartSendString((uint8_t*)"\n\rParity: ");
	  uartSendString((uint8_t*)parityValue);
	  uartSendString((uint8_t*)"\n\r");

	  return successfulInitialization;
}

/* Función que envia un mensaje por UART.
 * Recibe un punto a array como parametro, el cual contiene el mensaje a enviar.*/
void uartSendString(uint8_t * pstring){
	HAL_UART_Transmit(&UartHandle,(uint8_t*) pstring,strlen((const char*) pstring), 1000);
}

/* Función que envia un mensaje por UART.
 * Recibe un punto a array como parametro, el cual contiene el mensaje a enviar.
 * Tambien se debe indicar la cantidad de caracteres que deben ser enviados.*/
void uartSendStringSize(uint8_t * pstring, uint16_t size){
	HAL_UART_Transmit(&UartHandle,(uint8_t*) pstring,size, 0xFFFF);
}
