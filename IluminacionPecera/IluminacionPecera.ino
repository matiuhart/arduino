/*
 Codigo escrito para encendido y apagado de iluminacion para una pecera.
 Cuando por serie se recibe un "on", la ilumincaion es encendida a travez de los pines 9 y 10, cuando es recibido un "off" se apagan ambos 
 
 */

int pines[] = {9,10};            // Pines utilizar
int pinesCantidad = 3;           // Cantidad de pines a utilizar
boolean estadoLuz = false;       // Estado de la iluminación
String inputString = "";         // Variable que almacena cada cadena entrante al puerto serie
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

  // Llamo a la funcion de evento serie para verificar entrada de datos
  serialEvent();
  
  // Imprime la cadena cuando llega una nueva linea:
  if (stringComplete) {
    //Serial.println(inputString);

    // Analizo el valor de la cadena para encender o apagar iluminación
    if(inputString == "on"){
      estadoLuz = true;
      Serial.println("Luces Encendidas");
    }
    else if (inputString == "off"){
          estadoLuz = false;
          Serial.println("Luces Apagadas");
    }
    
    // Limpio la cadena para esperar nuevos datos entrantes
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
    Serial.println(inChar);
    
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


