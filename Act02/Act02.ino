const char startByte = '#';
const char stopByte = '$';
const uint8_t bufferSize = 5;


uint8_t startFound = 0;
uint8_t byteCounter = 0;

int i = 0;

char buffer[bufferSize];

void setup() {

  Serial.begin(9600);               // Inicializa el puerto
  while(!Serial);                   // Checa que este inicializado
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);

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
          
          // Revisar el caracter COMMAND
          if (buffer[1] != 'W' && buffer[1] != 'R') Serial.print ("#E03$");
          // Revisar el PIN
          else if (buffer[2] != '2' && buffer[2] != '4' && buffer[2] != '7') Serial.print ("#E04$");
          // Revisar VALUE
          else if (buffer[3] != '0' && buffer[3] != '1' && buffer[3] != '?') Serial.print ("#E05$");
          else {
             if (buffer[1]=='W' && buffer[3] != '?'){
              digitalWrite(buffer[2]-'0', buffer[3]-'0');
              Serial.print("#A" + String(buffer[2]) + String(buffer[3]) + "$");
            }
            if (buffer[1]=='R' && buffer[3]=='?'){
              Serial.print ("#A" + String(buffer[2]) + digitalRead(buffer[2]-'0') + "$");
            }
                
          startFound = 0;
          } 
        }
        else {
          // el mensaje no se recibió correctamente
          startFound = 0;
          Serial.print("#E02$");
        }
      }
    } else {
      Serial.print("#E01$");
    }
  }
}
