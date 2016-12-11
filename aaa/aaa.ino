/*
 Codigo escrito para encendido y apagado de iluminacion para una pecera.
 Cuando por serie se recibe un "on", la ilumincaion es encendida a travez de los pines 9 y 10, cuando es recibido un "off" se apagan ambos 
 
 */
 
int pines[] = {11,10};            // Pines utilizar
int pinesCantidad = 3;           // Cantidad de pines a utilizar
boolean estadoLuz = false;       // Estado de la iluminación
String inputString = "";         // Variable que almacena cada cadena entrante al puerto serie
char inputChar []= {};
boolean stringComplete = false;  // Define si se completó la cadena

void setup() {
  // Inicializo puerto serie
  Serial.begin(9600);
  
  // reserva 200 bytes para inputString:
  inputString.reserve(200);
  
  // Declaro pines de salida
  for (int pinNro = 0; pinNro < pinesCantidad; pinNro++ ){
    pinMode(pines[pinNro],OUTPUT);
  }
}

void loop() {

	// Modifico array dinamicamente y convierto string to char
    char inputChar[inputString.length()+1];
    inputString.toCharArray(inputChar,inputString.length()+1);

  
	// Llamo a la funcion de evento serie para verificar entrada de datos
	serialEvent();

	// Imprime la cadena cuando llega una nueva linea:
	if (stringComplete) {

	Serial.println(inputString);

	//imprimirChars();

	char modo = inputString[0];
	//inputString.substring(0,1).getBytes(modo,3);

	switch (modo) {
	    case 's':
	       	estadoLuz = true;
	      	Serial.println("Modo seteo activado");
	    
	      break;
	    case 'g':
	    	estadoLuz = false;
	    	Serial.println("Modo consulta activado");
	    
	      break;
	    default:
	      Serial.println("Ingrese un comando valido");
	}


	// Limpio la cadena para esperar nuevos datos entrantes
	memset(inputChar, 0, sizeof(inputChar));
	inputString = "";
	stringComplete = false;
	}

	// Enciendo o apago todos los pines de iluminacion
	for (int pinNro = 0; pinNro < pinesCantidad; pinNro++ ){
	digitalWrite(pines[pinNro],estadoLuz);
	}
  
}


/////////////////////////////////////////////////////////// FUNCIONES ////////////////////////////////////////////////////////////////////


// Evento en serie (Lee cadena entrante a puerto serie y luego de un "\n" almacena el string en inputString)
void serialEvent() {
  while (Serial.available()) {
    
    // Toma un nuevo byte
    char inChar = (char)Serial.read();
       
    // Si el caracter entrante es una nueva linea (\n) se setea el flag de cadena completa (StringComplete) en true sino agrega el char a inputString
    if (inChar == '\n') {
      stringComplete = true;
      // Quito el caracter de nueva linea (\n) de inputString
      inputString.trim();

    
    }
    else{
      // Agrego la cadena a inputString:
      inputString += inChar;

      
    }
  }
}

void imprimirChars(){
  	// Imprimo los caracteres dentro del array
    for (int i=0;i < inputString.length();i++) {
        
        Serial.println(inputChar[i]);
        
    }
}

