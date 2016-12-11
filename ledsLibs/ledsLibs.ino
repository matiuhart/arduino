/*
ESTA ES UN LIBRERIA PROGRAMADA PARA PRUEBAS DE TRABAJO CON CLASES
*/

#include <ledsLibs.h>

// Variable global para ser recuperada desde clase y asignar el valor a variable privada valorMensaje de clase
String mensaje;

// Instancio la clase
ledsLibs encender;

void setup() {
	Serial.begin(9600);
  
}

void loop() {

	// Cambio valor de mensaje
	mensaje = "holis";

	// Paso el valor de mensaje a la clase
	encender.mensajes(mensaje);

  	// Parpadeo de led en pin 15
  	encender.parpadear(15,1500);

  	// Led en pin 14 estático	
  	encender.estatico(14);

  	// Cambio nuevamente el valor de mensaje
  	mensaje = "hola";
  	encender.mensajes(mensaje);


}
