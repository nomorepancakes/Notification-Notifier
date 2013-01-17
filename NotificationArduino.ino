void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(17, INPUT);
}
int Del = 10;
int State = 0, StateCustom = 0;
int pi = 0;
void loop() {
  checkSerial(0);
  if (State == 1) {
     fade();
  };
  if (State == 2) {
     blunk();
  }
  if (State == 3) {
    multipleblunk();
  }
  if (State == 40) {
    custom();
  }
}
void blunk() {
  for(int xi = 0;xi < 5; xi++) {
    digitalWrite(7, HIGH);
    delay(70);
    digitalWrite(7, LOW);
    delay(70);
    pi = pi + 1;
    if (pi == 8) { delay(700); pi = 0; }
    if (xi == 4) {
      xi = 0;
      //delay(20);
    }
    checkSerial(0);
    if (State == 35) {    //breakout.
      digitalWrite(7, LOW);
      xi = 99;pi=0;
    }
    if(State == 1){fade();xi=99;pi=0;};
    if(State==3){multipleblunk();xi=99;pi=0;};
    }
}
void fade() {
 int  x = 1;
 int Inc = 1;
   while(x < 255) {
      analogWrite(7, x);
      x = x + Inc;
      delay(Del);
      if (x == 254) {
        Inc = -1;
        Del = 15; 
      };
      if (x == 0) {
        Inc = 1; 
        digitalWrite(7, LOW);
        delay(5000);
        Del = 10;
      };
      checkSerial(0);
      if (State == 35){  //breakout.
        x = 256;
        digitalWrite(7, LOW);
      };
      if(State==2){blunk();x=256;};
      if(State==3){multipleblunk();x=256;};
    }
}
void multipleblunk() {
  for(int xi = 0;xi < 11; xi++) {
    digitalWrite(7, HIGH);
    delay(150);
    digitalWrite(4, HIGH);
    delay(150);
    digitalWrite(2, HIGH);
    delay(150);
    
    digitalWrite(7, LOW);
    delay(150);
    digitalWrite(4, LOW);
    delay(150);
    digitalWrite(2, LOW);
    delay(1000);
    if (xi == 10) {xi == 0;};
    
    checkSerial(0);
    if (State == 35) {    //breakout.
      digitalWrite(7, LOW);
      digitalWrite(4, LOW);
      digitalWrite(2, LOW);
      xi = 99;
    }
    if (State == 1){fade();xi=99;};
    if (State == 2){blunk();xi=99;};
  }
}

void custom() {
  while(1){
    checkSerialCustom(0);
    if (StateCustom == 1) {
      if (Serial.available() > 2) {
        int pin = Serial.read();
        int mode = Serial.read();
        int interval = Serial.read();
        digitalWrite(pin, mode);
        delay(interval);
      }
    }
  }
}
  

void checkSerial(int seav){
  if (Serial.available() > seav) {
    State = Serial.read();
  }
/*  if (digitalRead(17)==HIGH) {
    State = 35;
  } */
} //Will try that when I get a button. Works ok with just a resistor.
void checkSerialCustom(int seav) {
  if (Serial.available() > seav) {
    StateCustom = Serial.read();
  }
}
