#include <ledsLibs.h>

ledsLibs::ledsLibs(){}

// Funcion para parpadeo de led
void ledsLibs::parpadear(int pin, int time){

	// Setea el pin en modo salida
	pinMode(pin, OUTPUT);

	// Enciende y apaga
	digitalWrite(pin, HIGH);
	delay(time);
	digitalWrite(pin, LOW);
	delay(time);
}

// Funcion para encendido estatico
void ledsLibs::estatico(int pin){

	// Setea el pin en modo salida
	pinMode(pin, OUTPUT);

	// Enciende de manera estatica
	digitalWrite(pin, HIGH);
}

// Funcion de prueba para accesar a valores de variables globales
void ledsLibs::mensajes(String mensaje){

	valorMensaje = mensaje;
	Serial.println(valorMensaje);
}