/*
 * API_gpio.c
 *
 *  Created on: 26 sep. 2022
 *      Author: MATIAS
 */

#include <stdint.h>
#include "API_display.h"
#include "API_gpio.h"

/*gpioDisplay_init:
 *Configura los puertos D0 a D6 como salidas.*/
void gpioDisplay_init(void){

	GPIO_InitTypeDef gpioInit={0};

	/*Habilita clocks para los puertos E,F y G.*/
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/*Configuración de los pines D3, D5 y D6 (ubicados en puerto E) como salidas.*/
	gpioInit.Pin = (D3_PIN | D5_PIN | D6_PIN);
	gpioInit.Mode= GPIO_MODE_OUTPUT_PP;
	gpioInit.Pull = GPIO_NOPULL;
	gpioInit.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(D3_PORT, &gpioInit);

	/*Configuración de los pines D2 y D4 (ubicados en puerto F) como salidas.*/
	gpioInit.Pin = (D2_PIN | D4_PIN);
	gpioInit.Mode= GPIO_MODE_OUTPUT_PP;
	gpioInit.Pull = GPIO_NOPULL;
	gpioInit.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(D2_PORT, &gpioInit);

	/*Configuración de los pines D0 y D1 (ubicados en puerto G) como salidas.*/
	gpioInit.Pin = (D0_PIN | D1_PIN);
	gpioInit.Mode= GPIO_MODE_OUTPUT_PP;
	gpioInit.Pull = GPIO_NOPULL;
	gpioInit.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(D0_PORT, &gpioInit);

	/*Pone en estado LOW a los pines antes nombrados*/
	HAL_GPIO_WritePin(D3_PORT,D3_PIN|D5_PIN| D6_PIN, LOW);
	HAL_GPIO_WritePin(D2_PORT,D2_PIN|D4_PIN, LOW);
	HAL_GPIO_WritePin(D0_PORT,D0_PIN|D1_PIN, LOW);
}

/*gpioButton_init:
 *Configura el puerto D15 como entrada.*/
void gpioButton_init(void){

	GPIO_InitTypeDef gpioButtonInit={0};

	/*Habilita clock para el puerto B.*/
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configuracion del pin D15 como entrada.*/
	gpioButtonInit.Pin = (D15_PIN);
	gpioButtonInit.Mode= GPIO_MODE_INPUT;
	gpioButtonInit.Pull = GPIO_PULLUP;
	gpioButtonInit.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(D15_PORT, &gpioButtonInit);
}

/*gpioButton_Read:
 *Función que devuelve el estado del interruptor externo (conectado en D15).
 *Si el pulsador esta presionado, devuelve un estado booleano TRUE.
 *Si el pulsador esta liberado, devuelve un estado booleano FALSE.*/
bool_t gpioButton_Read(void){
	bool_t stateButton=false;

	/*Debido a la configuración del puerto D15 como entrada PULL UP, al presionarlo
	 *setea un estado BAJO al puerto D15.
	 *Para invertirlo a estado ALTO, se niega la consulta HAL_GPIO_ReadPin dentro del condicional IF.*/
	if(!HAL_GPIO_ReadPin(D15_PORT, D15_PIN)){
		stateButton=true;
	}
	else{
		stateButton=false;
	}
	return stateButton;
}

/*gpioDisplay_write:
 *Actualiza el estado de los puertos D0 a D6, generando la representación de números en el display.*/
void gpioDisplay_write(uint8_t valorDisplay){
	uint8_t estadoLed[NUMERO_LEDS_DISPLAY];
	uint8_t representacion;

	/*Verifica si el parámetro de entrada es el adecuado.*/
	if (valorDisplay == NRO_CERO || valorDisplay == NRO_UNO ||
	    valorDisplay == NRO_DOS || valorDisplay == NRO_TRES ||
		valorDisplay == NRO_CUATRO || valorDisplay == NRO_CINCO ||
		valorDisplay == NRO_SEIS || valorDisplay == NRO_SIETE ||
		valorDisplay == NRO_OCHO || valorDisplay == NRO_NUEVE){
		representacion=valorDisplay;
	}
	else{
		/*En caso de no serlo, enciende LED1 de manera permanente*/
		while(1){
			BSP_LED_On(LED1);
		}
	}

	for (int i=0;i<NUMERO_LEDS_DISPLAY;i++){
		/*Se separa y analiza cada bit del array de entrada.
		 *Se genera un nuevo array en donde se almacena el estado que deber adquirir cada puerto GPIO de salida.
		 *Si el bit posee un valor 1, se le asigna estado HIGH.
		 *Si el bit posee un valor 0, se le asigna un estado LOW*/
		if((representacion>>i)&MASCARA_SEPARA_BITS){
			estadoLed[i]=HIGH;
		}
		else{
			estadoLed[i]=LOW;
		}
	}

	/*Setea los estados de los puertos GPIO en HIGH o LOW, segun corresponda.*/
	HAL_GPIO_WritePin(D0_PORT, D0_PIN, 	estadoLed[0]);
	HAL_GPIO_WritePin(D1_PORT, D1_PIN,	estadoLed[1]);
	HAL_GPIO_WritePin(D2_PORT, D2_PIN, 	estadoLed[2]);
	HAL_GPIO_WritePin(D3_PORT, D3_PIN, 	estadoLed[3]);
	HAL_GPIO_WritePin(D4_PORT, D4_PIN, 	estadoLed[4]);
	HAL_GPIO_WritePin(D5_PORT, D5_PIN, 	estadoLed[5]);
	HAL_GPIO_WritePin(D6_PORT, D6_PIN, 	estadoLed[6]);
}
