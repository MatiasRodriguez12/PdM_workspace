# PdM_workspace
STM32CubeIDE workspace para Programación de microcontroladores - CESE - FIUBA

Autor: Rodriguez, Matías Nahuel

Practica 1: 
    Ejercicio 1
        Programa que se encarga de hacer parpadear 3 leds en secuencia. El tiempo de toggle de cada led es de 200 ms.
    Ejercicio 2
        Se agrega el uso de un pulsador. Dicho pulsador se encarga de cambiar la secuencia de encendido de los leds.

Practica 2:
    Programa que ejecuta el encedido/apagado de 3 led de manera independiente a traves de retardos no bloqueantes.
    Cada led posee un tiempo de toggle propio y diferente a los demas.
    
Practica 3:
    Modularizacion: se crea una API a partir de los retardos no bloqueantes diseñados en la Practica 2.
    Se diseña un programa que haga titilar los 3 leds en secuencia, utilizando los modulos antes mencionados.
    
Practica 4:
    4.1 -   Se implementa un sistema antirrebotes, utilizando una maquina de estados finita(MEF). 
            Cuando se presiona el pulsador, se togglea LED 1. Por otra parte, cuando se libera, se togglea LED 3.
    
    4.2 -   Se modulariza el sistema antirrebotes antes mencionado, y se los almacena en la carpeta API.
            Se crea un programa que modifica la frecuencia de toggle de LED2 cuando se presiona el pulsador, 
            aprovechando los modulos creados en las practicas 3 y 4.

Practica 5:
    Tomando como referencia el código ejemplo, se crean modulos API para poder utilizar comunicación UART.
    A partir de la practica 4.2, se modifica el código para que se envíe un mensaje por UART cada vez que
    se detecte una pulsación o liberación de boton válida.
