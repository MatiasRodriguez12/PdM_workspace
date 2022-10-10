/*
 * API_debounce.c
 *
 *  Created on: 14 sep. 2022
 *      Author: MATIAS
 */

#include "API_delay.h"
#include "API_debounce.h"
#include "API_gpio.h"
#include "API_uart.h"

/*readButton
 *Función privada utilizada para la lectura de pulsadores.
 *Devuelve un valor booleano TRUE si el pulsador en cuestión se encuentra presionado.
 *
 *Parametro: PULSADOR_UP/PULSADOR_DOWN*/
static bool_t readButton(uint8_t button);

/*buttonPressed
 *Función privada utilizada para la deteccion de pulsaciones.
 *
 *Parametro: PULSADOR_UP/PULSADOR_DOWN*/
static void buttonPressed(uint8_t button);

/*Variable global privada que adquiere estado TRUE cuando detecta una pulsación valida de BU.*/
static bool_t buttonUPPress;
/*Variable global privada que adquiere estado TRUE cuando detecta una pulsación valida de BD.*/
static bool_t buttonDOWNPress;

/*Estructuras para toma de tiempo y validación de pulsaciones BU y BD.*/
static delay_t delayButtonBU;
static delay_t delayButtonBD;

/*Estructura utilizada para analizar en la MEF.
 *Segun que pulsador se analice, se igualará a delayButtonBU o delayButtonBD. */
static delay_t delayButton;

/*Estructuras para almacenar estados BU y BD.*/
static debounceState_t StateBU;
static debounceState_t StateBD;

/*Estructura utilizada para analizar en la MEF.
 *Segun que pulsador se analice, se igualará a StateBU o StateBD. */
static debounceState_t buttonState;

/*debounceFSM_init
 *Se encarga de asignar el estado inicial en la MEF utilizada para validación de pulsaciones.
 *Por defecto, se asigna estado BUTTON_UP como inicial
 *Se inicializa las estructuras para toma de tiempo y validación de pulsaciones*/
void debounceFSM_init(void){
	StateBU=BUTTON_UP;
	StateBD=BUTTON_UP;
	delayInit(&delayButtonBU,TIME_VALID_PUSH);
	delayInit(&delayButtonBD,TIME_VALID_PUSH);
}

/*debounceFSM_update
 *Verifica el estado del pulsador y actualiza el estado de la MEF
 *
 *Parametro: PULSADOR_UP/PULSADOR_DOWN*/
void debounceFSM_update(uint8_t pulsador){

	uint8_t buttonSel=0;
	//Verifica valor de parametro de entrada, el cual indica que pulsador se debe analizar (BU o BD).
	if (pulsador==PULSADOR_UP){
		buttonState=StateBU;
		delayButton=delayButtonBU;
		buttonSel=PULSADOR_UP;
	}
	else if (pulsador==PULSADOR_DOWN){
		buttonState=StateBD;
		delayButton=delayButtonBD;
		buttonSel=PULSADOR_DOWN;
	}
	else{
		/*En caso de error en parametro, enciende LED1 de manera permanente*/
		while(1){
			BSP_LED_On(LED1);
		}
	}

	switch (buttonState){
		/*Estado BUTTON_UP:
		 * A traves de la función readButton lee el estado del pulsador que corresponda.
		 * Si detecta que el pulsador se encuentra presionado, actualiza la MEF a estado BUTTON_FALLING.
		 * En estas condiciones, inicia al contador para validación.
		 * Si detecta que el pulsador no se encuentra presionado, mantiene la MEF en estado BUTTON_UP. */
		case BUTTON_UP:

			if(readButton(buttonSel)){
				delayRead(&delayButton);
				buttonState=BUTTON_FALLING;
				}
			else{
				buttonState=BUTTON_UP;
			}
		break;

		/*Estado BUTTON_FALLING:
		* Verifica que se cumpla el retardo de tiempo para validar una pulsación.
		* A traves de la función readButton lee el estado del pulsador que corresponda.
		* Si detecta que el pulsador se encuentra presionado, actualiza la MEF a estado BUTTON_DOWN (pulsación detectada).
		* A su vez, llama a la funcion buttonPressed indicar dicha pulsacion.
		* Si detecta que el pulsador no se encuentra presionado, actualiza la MEF a estado BUTTON_UP (pulsación no válida). */
		case BUTTON_FALLING:

			if (delayRead(&delayButton)){
				if(readButton(buttonSel)){
					buttonState=BUTTON_DOWN;
					buttonPressed(buttonSel);
				}
				else{
					buttonState=BUTTON_UP;
				}
			}
			else{
				buttonState=BUTTON_FALLING;
			}
		break;

		/*Estado BUTTON_DOWN:
		* A traves de la función readButton lee el estado del pulsador que corresponda.
		* Si detecta que el pulsador no se encuentra presionado, actualiza la MEF a estado BUTTON_RAISING.
		* En estas condiciones, inicia al contador para validación.
		* Si detecta que el pulsador se encuentra presionado, mantiene la MEF en estado BUTTON_DOWN. */
		case BUTTON_DOWN:

			if(!readButton(buttonSel)){
				delayRead(&delayButton);
				buttonState=BUTTON_RAISING;
			}
			else{
				buttonState=BUTTON_DOWN;
			}
		break;

		/*Estado BUTTON_RAISING:
		* Verifica que se cumpla el retardo de tiempo para validar una pulsación.
		* A traves de la función readButton lee el estado del pulsador que corresponda.
		* Si detecta que el pulsador no se encuentra presionado, actualiza la MEF a estado BUTTON_UP (pulsador liberado).
		* Si detecta que el pulsador se encuentra presionado, actualiza la MEF a estado BUTTON_DOWN (liberación no válida). */
		case BUTTON_RAISING:

			if (delayRead(&delayButton)){
				if(!readButton(buttonSel)){
					buttonState=BUTTON_UP;
				}
				else{
					buttonState=BUTTON_DOWN;
				}
			}
			else{
				buttonState=BUTTON_RAISING;
			}
		break;

		/*Por default, vuelve al estado inicial*/
		default:
			debounceFSM_init();
		break;
	}
	/*Actualiza los valores de StateBU,delayButtonBU o StateBD,delayButtonBD segun corresponda*/
	if (buttonSel==PULSADOR_UP){
		StateBU=buttonState;
		delayButtonBU=delayButton;
	}
	else{
		StateBD=buttonState;
		delayButtonBD=delayButton;
	}
}

/*readButton
 *Función que lee el estado de los pulsadores.
 *Devuelve un valor booleano TRUE si el pulsador en cuestión se encuentra presionado. */
static bool_t readButton(uint8_t button){
	bool_t stateButton=false;

	/*Si se pasa por parametro PULSADOR_UP, se lee BU.*/
	if(button==PULSADOR_UP){
		stateButton=BSP_PB_GetState(BUTTON_USER);
	}
	/*Si se pasa por parametro PULSADOR_DOWN, se lee BD.*/
	else if(button==PULSADOR_DOWN){
		stateButton=gpioButton_Read();
	}
	/*Para cualquier otro parametro de entrada, devuelve FALSE.*/
	else{
		stateButton=false;
	}
	return stateButton;
}

/*buttonPressed
 *Función que indica que boton fue presionado.
 *Asigna un valor booleano TRUE a las variables buttonUPPress o buttonDOWNPress, segun corresponda. */
static void buttonPressed(uint8_t button) {
	if(button==PULSADOR_UP){
		buttonUPPress=true;
	}
	else{
		buttonDOWNPress=true;
	}
}

/*readKeyUP
 *Función booleana que devuelve una copia del valor de la variable buttonUPPress.
 *Si dicha variable posee valor lógico TRUE, la reinicializa a FALSE.*/
bool_t readKeyUP(void){
	bool_t buttonStateAux;

	if (buttonUPPress==true){
		buttonStateAux=true;
		buttonUPPress=false;
	}
	else{
		buttonStateAux=false;
	}
	return buttonStateAux;
}

/*readKeyDOWN
 *Función booleana que devuelve una copia del valor de la variable buttonDOWNPress.
 *Si dicha variable posee valor lógico TRUE, la reinicializa a FALSE.*/
bool_t readKeyDOWN(void){
	bool_t buttonStateAux;

	if (buttonDOWNPress==true){
		buttonStateAux=true;
		buttonDOWNPress=false;
	}
	else{
		buttonStateAux=false;
	}
	return buttonStateAux;
}
