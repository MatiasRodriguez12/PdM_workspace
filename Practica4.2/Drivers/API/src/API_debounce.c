/*
 * API_debounce.c
 *
 *  Created on: 14 sep. 2022
 *      Author: MATIAS
 */

#include "API_debounce.h"
#include "API_delay.h"

//Declaración de estructura para estados de MEF
typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t;

//Prototipos de funciones privadas
/*buttonPressed
 *Cuando se presione el pulsador, se togglea LED1*/
static void buttonPressed(void);

/*buttonReleased
 *Cuando se libera el pulsador, se togglea LED3*/
static void buttonReleased(void);

//Variable global privada que adquiere estado TRUE cuando detecta una pulsación valida
static bool_t buttonPress;

//Estructura para toma de tiempo y validación de pulsaciones
static delay_t delayButton;

//Estructura para definir estados de MEF a utilizar
static debounceState_t buttonState;

/*debounceFSM_init
 *Se encarga de asigar el estado inicial en la MEF utilizada para validación de pulsaciones
 *Por defecto, se asigna estado BUTTON_UP como inicial
 *Se inicializa la estructura para toma de tiempo y validación de pulsaciones*/
void debounceFSM_init(void){
	buttonState=BUTTON_UP;
	delayInit(&delayButton,TIME_VALID_PUSH);
}

/*debounceFSM_update
 *Verifica el estado del pulsador y actualiza el estado de la MEF*/
void debounceFSM_update(void){

	switch (buttonState){
		/*Estado BUTTON_UP:
		 * Si detecta que el pulsador se encuentra presionado, actualiza la MEF a estado BUTTON_FALLING.
		 * A su vez, se inicia el contador para validacion.
		 * Si detecta que el pulsador no se encuentra presionado, mantiene la MEF en estado BUTTON_UP. */
		case BUTTON_UP:
			if(BSP_PB_GetState(BUTTON_USER)){
				buttonState=BUTTON_FALLING;
				delayRead(&delayButton);
			}
			else{
				buttonState=BUTTON_UP;
			}
		break;

		/*Estado BUTTON_FALLING:
		* Verifica que se cumpla el retardo de tiempo para validar una pulsación.
		* Si detecta que el pulsador se encuentra presionado, actualiza la MEF a estado BUTTON_DOWN (pulsación detectada).
		* A su vez, llama a la funcion buttonPressed para togglear LED 1.
		* Si detecta que el pulsador no se encuentra presionado, actualiza la MEF a estado BUTTON_UP (pulsación no válida). */
		case BUTTON_FALLING:
			if (delayRead(&delayButton) == true){
				if(BSP_PB_GetState(BUTTON_USER)){
					buttonState=BUTTON_DOWN;
					buttonPressed();
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
		* Si detecta que el pulsador no se encuentra presionado, actualiza la MEF a estado BUTTON_RAISING.
		* A su vez, se inicia el contador para validacion.
		* Si detecta que el pulsador se encuentra presionado, mantiene la MEF en estado BUTTON_DOWN. */
		case BUTTON_DOWN:
			if(!BSP_PB_GetState(BUTTON_USER)){
				buttonState=BUTTON_RAISING;
				delayRead(&delayButton);
			}
			else{
				buttonState=BUTTON_DOWN;
			}
		break;

		/*Estado BUTTON_RAISING:
		* Verifica que se cumpla el retardo de tiempo para validar una pulsación.
		* Si detecta que el pulsador no se encuentra presionado, actualiza la MEF a estado BUTTON_UP (pulsador liberado).
		* A su vez, llama a la funcion buttonReleased para togglear LED 3.
		* Si detecta que el pulsador se encuentra presionado, actualiza la MEF a estado BUTTON_DOWN (liberación no válida). */
		case BUTTON_RAISING:
			if (delayRead(&delayButton) == true){
				if(!BSP_PB_GetState(BUTTON_USER)){
					buttonState=BUTTON_UP;
					buttonReleased();
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

}

/*buttonPressed
 *Función que togglea LED1.
 *A su vez, asigna valor logico TRUE a la variable buttonPress */
static void buttonPressed(void) {
	BSP_LED_Toggle(LED1);
	buttonPress=true;
}

/*buttonReleased
 *Función que togglea LED3. */
static void buttonReleased(void){
	BSP_LED_Toggle(LED3);
}

/*readKey
 *Función booleana que devuelve una copia del valor de la variable buttonPress.
 *Si dicha variable posee valor lógico TRUE, la reinicializa a FALSE.*/
bool_t readKey(void){
	bool_t buttonStateAux;

	if (buttonPress==true){
		buttonStateAux=true;
		buttonPress=false;
	}
	else{
		buttonStateAux=false;
	}
	return buttonStateAux;
}
