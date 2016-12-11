#ifndef LEDSLIBS_H
#define LEDSLIBS_H

#include <Arduino.h>

class ledsLibs
{
public:
	ledsLibs();
	
	// Parpadeo
	void parpadear(int pin, int time);

	// Encendido statico
	void estatico(int pin);

	// Metodo para guardar valor de mensaje y recuperar el valor de una variable global
	void mensajes(String mensaje);

private:
	// Variable privada para asignar el valor de la global
	String valorMensaje;
};

#endif