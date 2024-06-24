uint8_t send_com=2;
uint8_t W_R=3;    // 1
uint8_t MSB=4;    // 2
uint8_t MB=5;     // 3
uint8_t LSB=6;    // 4
uint8_t val_pin=7;
uint8_t ant=0;
char w_r;
char val;
int pin_num=0;

const int led_val=8;
const int led_e4=9;
const int led_e5=10;
const int led_2=11;
const int led_4=12;
const int led_7=13;

void setup(){
  // Code
  pinMode(send_com, INPUT);
  pinMode(W_R, OUTPUT);
  pinMode(MSB, OUTPUT);
  pinMode(MB, OUTPUT);
  pinMode(LSB, OUTPUT);
  pinMode(val_pin, OUTPUT);
  
  pinMode(led_val, OUTPUT);
  pinMode(led_e4, OUTPUT);
  pinMode(led_e5, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_7, OUTPUT);
  
  Serial.begin(9600);
  while(!Serial);
  ant=digitalRead(send_com);
}

void loop(){
  // Code
  if(ant!=digitalRead(send_com)){
    if(ant==0){
      // Construir mensaje
      if(digitalRead(W_R)==1){
        w_r='W';
        val=digitalRead(val_pin)+'0';
      }
      else{
        w_r='R';
        val='?';
      }
      pin_num=digitalRead(MSB)*4 + digitalRead(MB)*2 + digitalRead(LSB);
      Serial.print("#" + String(w_r) + String(pin_num) + String(val) + "$");
    }
    ant=digitalRead(send_com);
  }
}
