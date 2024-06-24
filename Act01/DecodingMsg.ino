const char startByte = '#';
const char stopByte = '$';
const uint8_t bufferSize = 5;


uint8_t startFound = 0;
uint8_t byteCounter = 0;

int i = 0;

char buffer[bufferSize];

const int ledPin = 13; 

void setup() {

  Serial.begin(9600);               // Inicializa el puerto
  while(!Serial);                   // Checa que este inicializado
  pinMode(ledPin, OUTPUT); // Configura el pin del LED como salida

}

void loop() {
  // Revisamos que el buffer de recepcion contenga algun caracter
  if (Serial.available() > 0) {
    // Leemos el primer caracter disponible
    char c = Serial.read();
    // Revisamos si c corresponde con el caracter de inicio de mensaje
    if (c == startByte) {
      startFound = 1;
      byteCounter = 0;
    }
    // Si ya se reconoció el inicio del mensaje lo almacenamos en el buffer
    if (startFound == 1) {
      // Guardamos los caracteres recibidos en el buffer del mensaje
      buffer[byteCounter] = c;
      byteCounter++;
      // Revisamos si se recibieron todos los caracteres esperados
      if (byteCounter >= bufferSize) {
        byteCounter = 0;
        // Revisamos si el último caracter corresponde con el de stop
        if (buffer[4] == stopByte) {
          // Decodificamos el mensaje
          for(i=0; i<bufferSize; i++){
            
            char command = buffer[1];
            char pin = buffer[2];
            char value = buffer[3];

            // Revisar que el caracter de COMMAND corresponda con el caracter 'W' o 'R'
            if (command == 'W' || command == 'R') {
              // Revisar que el caracter de PIN corresponda con el número '2', '4', o '7'
              if (pin == '2' || pin == '4' || pin == '7') {
                // Revisar que el caracter de VALUE corresponda con '0' y '1' si COMMAND es 'W'
                // Si COMMAND es 'R', VALUE acepta solo el caracter '?'
                if ((command == 'W' && (value == '0' || value == '1')) || (command == 'R' && value == '?')) {
                  } else {
                  Serial.println("Mensaje Descartado. Error 05: Valor incorrecto para VALUE.");
                  return;
                }
              } else {
                Serial.println("Mensaje Descartado. Error 04: Valor incorrecto para PIN.");
                return;
              }
            } else {
              Serial.println("Mensaje Descartado. Error 03: Valor incorrecto para COMMAND.");
              return;
            }
            Serial.println(buffer[i]);
            // Enciende el LED cuando el mensaje se valida
            digitalWrite(ledPin, HIGH);
            delay(1000); // Mantiene el LED encendido durante 1 segundo
            digitalWrite(ledPin, LOW); // Apaga el LED
          }
          startFound = 0;
        } else {
          // el mensaje no se recibió correctamente
          Serial.println("Mensaje Descartado. Error 02: StopByte no encontrado");
        }
      }
    } else {
      Serial.println("Mensaje Descartado. Error 01: StartByte no identificado");
    }
  }
}
