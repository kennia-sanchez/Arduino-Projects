const char startByte = '[';
const char stopByte = ']';
const uint8_t bufferSize = 5;


uint8_t startFound = 0;
uint8_t byteCounter = 0;

int i = 0;
int grados = 0;

char buffer[bufferSize];

void setup() {

  Serial.begin(9600);               // Inicializa el puerto
  while(!Serial);                   // Checa que este inicializado
  pinMode(2, INPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  if (digitalRead(3) == HIGH) {
    digitalWrite(10, HIGH); // Prende LED correspondiente al botón 3
  } else {
    digitalWrite(10, LOW); // Apaga LED correspondiente al botón 3
  }
  
  if (digitalRead(7) == HIGH) {
    digitalWrite(11, HIGH); // Prende LED correspondiente al botón 7
  } else {
    digitalWrite(11, LOW); // Apaga LED correspondiente al botón 7
  }
  
  if (digitalRead(8) == HIGH) {
    digitalWrite(12, HIGH); // Prende LED correspondiente al botón 8
  } else {
    digitalWrite(12, LOW); // Apaga LED correspondiente al botón 8
  }
  
  if (digitalRead(9) == HIGH) {
    digitalWrite(13, HIGH); // Prende LED correspondiente al botón 9
  } else {
    digitalWrite(13, LOW); // Apaga LED correspondiente al botón 9
  }
  
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
          if (buffer[1] != 'L' && buffer[1] != 'B' && buffer[1] != 'M' && buffer[1] != 'E') Serial.print ("[E00]");
          // Revisar el PIN
          else if (buffer[2] != '2' && buffer[2] != '3' && buffer[2] != '4' && buffer[2] != '5' && buffer[2] != '6' && buffer[2] != '7' && buffer[2] != '8' && buffer[2] != '9' && buffer[2] != 'A' && buffer[2] != 'B' && buffer[2] != 'C' && buffer[2] != 'D') Serial.print ("[E00]");
          // Revisar VALUE
          else if (buffer[3] != '0' && buffer[3] != '1' && buffer[3] != '?') Serial.print ("[E00]");
          else {
            
            // Revisar si el Pin es correcto para el LED
            if (buffer[1] == 'L') {
              if (buffer[2] == 'A') {
                if (buffer[3] == '1' || buffer[3] == '0') {
                  digitalWrite(10, buffer[3] - '0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                } else {
                  // Valor no válido
                  Serial.print("[E00]");
                }
              } else if (buffer[2] == 'B') {
                if (buffer[3] == '1' || buffer[3] == '0') {
                  digitalWrite(11, buffer[3] - '0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                } else {
                  // Valor no válido
                  Serial.print("[E00]");
                }
              } else if (buffer[2] == 'C') {
                if (buffer[3] == '1' || buffer[3] == '0') {
                  digitalWrite(12, buffer[3] - '0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                } else {
                  // Valor no válido
                  Serial.print("[E00]");
                }
              } else if (buffer[2] == 'D') {
                if (buffer[3] == '1' || buffer[3] == '0') {
                  digitalWrite(13, buffer[3] - '0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                } else {
                  // Valor no válido
                  Serial.print("[E00]");
                }
              } else {
                // Carácter de PIN no válido
                Serial.print("[E00]");
              }
            }


            // Revisar si el Pin es correcto para el Boton
            if (buffer[1] == 'B') {
              if (buffer[2] == '3' || buffer[2] == '7' || buffer[2] == '8' || buffer[2] == '9') {
                if (buffer[3] == '?') {
                  Serial.print ("[A" + String(buffer[2]) + digitalRead(buffer[2]-'0') + "]");
                } 
                else {
                  // Valor no válido
                  Serial.print("[E00]");
                }
              }
              else {
                // Carácter de PIN no válido
                Serial.print("[E00]");
              }
            }
            
            
            // Revisa si el Pin es correcto para el Motor
            if (buffer[1]=='M' && (buffer[2] == '5' || buffer[2] == '6')){
              switch(buffer[3]){
                case '0':
                  grados = 0;
                  digitalWrite(buffer[2]-'0', buffer[3]-'0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                  break;
                
                case '1':
                  grados = 45;
                  digitalWrite(buffer[2]-'0', buffer[3]-'0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                  break;
                
                case '2':
                  grados = 90;
                  digitalWrite(buffer[2]-'0', buffer[3]-'0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                  break;
                
                case '3':
                  grados = 135;
                  digitalWrite(buffer[2]-'0', buffer[3]-'0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                  break;
                
                case '4':
                  grados = 180;
                  digitalWrite(buffer[2]-'0', buffer[3]-'0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                  break;
                
                case '5':
                  grados = 225;
                  digitalWrite(buffer[2]-'0', buffer[3]-'0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                  break;
                
                case '6':
                  grados = 270;
                  digitalWrite(buffer[2]-'0', buffer[3]-'0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                  break;
                
                case '7':
                  grados = 315;
                  digitalWrite(buffer[2]-'0', buffer[3]-'0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                  break;
                
                case '8':
                  grados = 360;
                  digitalWrite(buffer[2]-'0', buffer[3]-'0');
                  Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
                  break;
              }
            }

            // Revisa si el Pin es correcto para el Encoder
            if (buffer[1]=='E' && (buffer[2] == '2' || buffer[2] == '4') && (buffer[3] == '1' || buffer[3] == '0')){
              digitalWrite(buffer[2]-'0', buffer[3]-'0');
              Serial.print("[A" + String(buffer[2]) + String(buffer[3]) + "]");
            }
            
          }

          
          startFound = 0;
        } else {
          // el mensaje no se recibió correctamente
          startFound = 0;
          Serial.print("[E00]");
        }
      }
    } else {
      Serial.print("[E00]");
    }
  }
}
