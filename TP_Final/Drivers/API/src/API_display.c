/*
 * API_display.c
 *
 *  Created on: 27 sep. 2022
 *      Author: MATIAS
 */

#include <string.h>
#include "API_debounce.h"
#include "API_display.h"
#include "API_uart.h"

/*Se declara la MEF para manejo de display.*/
static displayState_t stateDisplay;

/*Variable privada que almacena el array de estados de puertos GPIO.*/
static uint8_t numeroDisplay;

/*Variables booleanas privadas utilizadas para la detección de pulsaciones.*/
static bool_t displayUP=false;
static bool_t displayDOWN=false;

/*Variables privadas utilizadas para la comunicacion por UART.*/
static uint8_t nuevoValor[]="\n\rEl valor en display es: ";
static uint8_t BUpress[]="\n\n\rButton UP presionado. ";
static uint8_t BDpress[]="\n\n\rButton DOWN presionado. ";

/*Función privada que envia el mensaje por UART.*/
static void sendValueToUart(void);

/*displayFSM_init().
 *Funcion que inicializa la MEF de display.
 *A su vez, inicializa la UART.
 *Si inicia correctamente, setea LED 2 y asigna al estado 0 como estado inicial de la MEF de display.
 *Envia mensaje por UART indicando el estado inicial de la MEF.*/
void displayFSM_init(void){
	if(uartInit()){
		BSP_LED_On(LED2);
		stateDisplay=State_0;
		numeroDisplay=NRO_CERO;
		sendValueToUart();
	}
}

/*displayFSM_update().
 *Función que actualiza el estado la MEF de display.*/
void displayFSM_update(void){

	switch(stateDisplay){

		/*Si se detecta pulsación en boton UP, se avanza al estado 1.
		 *Si se detecta pulsación en boton DOWN, se retroce al estado 9.
		 *Si no se detecta pulsación alguna, se mantiene en estado 0.
		 *Se actualiza el valor de array de estados en variable numeroDisplay.*/
		case State_0:
			if(readKeyUP()){
				stateDisplay=State_1;
				numeroDisplay=NRO_UNO;
				displayUP=true;
			}
			else if(readKeyDOWN()){
				stateDisplay=State_9;
				numeroDisplay=NRO_NUEVE;
				displayDOWN=true;
			}
			else{
				stateDisplay=State_0;
				numeroDisplay=NRO_CERO;
			}
		break;

		/*Si se detecta pulsación en boton UP, se avanza al estado 2.
		 *Si se detecta pulsación en boton DOWN, se retroce al estado 0.
		 *Si no se detecta pulsación alguna, se mantiene en estado 1.
		 *Se actualiza el valor de array de estados en variable numeroDisplay.*/
		case State_1:
			if(readKeyUP()){
				stateDisplay=State_2;
				numeroDisplay=NRO_DOS;
				displayUP=true;
			}
			else if(readKeyDOWN()){
				stateDisplay=State_0;
				numeroDisplay=NRO_CERO;
				displayDOWN=true;
			}
			else{
				stateDisplay=State_1;
				numeroDisplay=NRO_UNO;
			}
		break;

		/*Si se detecta pulsación en boton UP, se avanza al estado 3.
		 *Si se detecta pulsación en boton DOWN, se retroce al estado 1.
		 *Si no se detecta pulsación alguna, se mantiene en estado 2.
		 *Se actualiza el valor de array de estados en variable numeroDisplay.*/
		case State_2:
			if(readKeyUP()){
				stateDisplay=State_3;
				numeroDisplay=NRO_TRES;
				displayUP=true;
			}
			else if(readKeyDOWN()){
				stateDisplay=State_1;
				numeroDisplay=NRO_UNO;
				displayDOWN=true;
			}
			else{
				stateDisplay=State_2;
				numeroDisplay=NRO_DOS;
			}
		break;

		/*Si se detecta pulsación en boton UP, se avanza al estado 4.
		 *Si se detecta pulsación en boton DOWN, se retroce al estado 2.
		 *Si no se detecta pulsación alguna, se mantiene en estado 3.
		 *Se actualiza el valor de array de estados en variable numeroDisplay.*/
		case State_3:
			if(readKeyUP()){
				stateDisplay=State_4;
				numeroDisplay=NRO_CUATRO;
				displayUP=true;
			}
			else if(readKeyDOWN()){
				stateDisplay=State_2;
				numeroDisplay=NRO_DOS;
				displayDOWN=true;
			}
			else{
				stateDisplay=State_3;
				numeroDisplay=NRO_TRES;
			}
		break;

		/*Si se detecta pulsación en boton UP, se avanza al estado 5.
		 *Si se detecta pulsación en boton DOWN, se retroce al estado 3.
		 *Si no se detecta pulsación alguna, se mantiene en estado 4.
		 *Se actualiza el valor de array de estados en variable numeroDisplay.*/
		case State_4:
			if(readKeyUP()){
				stateDisplay=State_5;
				numeroDisplay=NRO_CINCO;
				displayUP=true;
			}
			else if(readKeyDOWN()){
				stateDisplay=State_3;
				numeroDisplay=NRO_TRES;
				displayDOWN=true;
			}
			else{
				stateDisplay=State_4;
				numeroDisplay=NRO_CUATRO;
			}
		break;

		/*Si se detecta pulsación en boton UP, se avanza al estado 6.
		 *Si se detecta pulsación en boton DOWN, se retroce al estado 4.
		 *Si no se detecta pulsación alguna, se mantiene en estado 5.
		 *Se actualiza el valor de array de estados en variable numeroDisplay.*/
		case State_5:
			if(readKeyUP()){
				stateDisplay=State_6;
				numeroDisplay=NRO_SEIS;
				displayUP=true;
			}
			else if(readKeyDOWN()){
				stateDisplay=State_4;
				numeroDisplay=NRO_CUATRO;
				displayDOWN=true;
			}
			else{
				stateDisplay=State_5;
				numeroDisplay=NRO_CINCO;
			}
		break;

		/*Si se detecta pulsación en boton UP, se avanza al estado 7.
		 *Si se detecta pulsación en boton DOWN, se retroce al estado 5.
		 *Si no se detecta pulsación alguna, se mantiene en estado 6.
		 *Se actualiza el valor de array de estados en variable numeroDisplay.*/
		case State_6:
			if(readKeyUP()){
				stateDisplay=State_7;
				numeroDisplay=NRO_SIETE;
				displayUP=true;
			}
			else if(readKeyDOWN()){
				stateDisplay=State_5;
				numeroDisplay=NRO_CINCO;
				displayDOWN=true;
			}
			else{
				stateDisplay=State_6;
				numeroDisplay=NRO_SEIS;
			}
		break;

		/*Si se detecta pulsación en boton UP, se avanza al estado 8.
		 *Si se detecta pulsación en boton DOWN, se retroce al estado 6.
		 *Si no se detecta pulsación alguna, se mantiene en estado 7.
		 *Se actualiza el valor de array de estados en variable numeroDisplay.*/
		case State_7:
			if(readKeyUP()){
				stateDisplay=State_8;
				numeroDisplay=NRO_OCHO;
				displayUP=true;
			}
			else if(readKeyDOWN()){
				stateDisplay=State_6;
				numeroDisplay=NRO_SEIS;
				displayDOWN=true;
			}
			else{
				stateDisplay=State_7;
				numeroDisplay=NRO_SIETE;
			}
		break;

		/*Si se detecta pulsación en boton UP, se avanza al estado 9.
		 *Si se detecta pulsación en boton DOWN, se retroce al estado 7.
		 *Si no se detecta pulsación alguna, se mantiene en estado 8.
		 *Se actualiza el valor de array de estados en variable numeroDisplay.*/
		case State_8:
			if(readKeyUP()){
				stateDisplay=State_9;
				numeroDisplay=NRO_NUEVE;
				displayUP=true;
			}
			else if(readKeyDOWN()){
				stateDisplay=State_7;
				numeroDisplay=NRO_SIETE;
				displayDOWN=true;
			}
			else{
				stateDisplay=State_8;
				numeroDisplay=NRO_OCHO;
			}
		break;

		/*Si se detecta pulsación en boton UP, se avanza al estado 0.
		 *Si se detecta pulsación en boton DOWN, se retroce al estado 8.
		 *Si no se detecta pulsación alguna, se mantiene en estado 9.
		 *Se actualiza el valor de array de estados en variable numeroDisplay.*/
		case State_9:
			if(readKeyUP()){
				stateDisplay=State_0;
				numeroDisplay=NRO_CERO;
				displayUP=true;
			}
			else if(readKeyDOWN()){
				stateDisplay=State_8;
				numeroDisplay=NRO_OCHO;
				displayDOWN=true;
			}
			else{
				stateDisplay=State_9;
				numeroDisplay=NRO_NUEVE;
			}
		break;

		/*Por default, se retorna la MEF a su estado inicial.*/
		default:
		displayFSM_init();
		break;
	}
}

/*getStateDisplay()
 *Función que devuelve una copia del array de estados de los puertos GPIO.
 *Si detecta que existió pulsación alguna, llama a la función sendValueToUart() para comunicarlo por UART.*/
uint8_t getStateDisplay(void){
	uint8_t representacionNumero;
	if(displayUP==true || displayDOWN==true){
		sendValueToUart();
	}
	representacionNumero = numeroDisplay;
	return representacionNumero;
}

/*sendValueToUart()
 *Función privada que comunica por UART la pulsación detectada.
 *Indica que boton fue presionado, junto con el valor expresado en el display.*/
static void sendValueToUart(void){
	uint8_t numero[NRO_CARACTERES_ESTADO]={};
	if (displayUP==true){
		uartSendString((uint8_t*)BUpress);
		displayUP =false;
	}
	if(displayDOWN==true){
		uartSendString((uint8_t*)BDpress);
		displayDOWN=false;
	}
	sprintf((char*) numero, "%d",(int) stateDisplay);
	uartSendString((uint8_t*)nuevoValor);
	uartSendString((uint8_t*)numero);
}
