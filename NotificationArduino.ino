int del = 10, state = 0, stateCustom = 0, pi = 0;

void setup() {
  Serial.begin(9600);
	pinMode(7, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(17, INPUT);
}
void loop() {
	checkSerial(0);
	if (state == 1) 
		fade();
	else if (state == 2) 
		blunk();
	else if (state == 3) 
		multipleblunk();
	else 
		delay(1000);
}
void blunk() {
	for(int xi = 0; xi < 5; xi++) {
		digitalWrite(7, HIGH);
		delay(70);
		digitalWrite(7, LOW);
		delay(70);
		pi = pi + 1;
		if (pi == 8) 
			delay(700); pi = 0;
	if (xi == 4) {
		xi = 0;
		//delay(20);
	}
	checkSerial(0);
	if (state == 35) {    //breakout.
		digitalWrite(7, LOW);
		xi = 99;
    pi=0;
	}
	if(state == 1){
		fade();
		xi=99;
		pi=0;
	}else if( state==3 ) { 
		multipleblunk();
		xi=99;
		pi=0;
		}
	}
}
void fade() {
	int Inc = 1; //change the incrementation level
	for(int x = 0; x < 255; x = x + Inc) {
		analogWrite(7, x);
		delay(del);
		if (x == 254) { //start fading
			Inc = -Inc;
			del = 15; 
		}
		if (x == 0) { //start glowing
			Inc = -Inc; 
			digitalWrite(7, LOW);
			delay(5000); //try to avoid using delay, causes problems.
			del = 10;
		}
		checkSerial(0);
		if (state == 35){  //getout
			digitalWrite(7, LOW);        
			break;
		}
		if(state==2){
			blunk();
			x=256;
		}
		if(state==3){
			multipleblunk();
			x=256;
		}
    }
}
void multipleblunk() { //obviously these is a better way... but no time.
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
		if (xi == 10)
			xi == 0;
		checkSerial(0);
		if (state == 35) {    //breakout.
			digitalWrite(7, LOW);
			digitalWrite(4, LOW);
			digitalWrite(2, LOW);
			break;
		}
		if (state == 1){
			fade();
			xi=99;
		}
		if (state == 2){
			blunk();
			xi=99;
		}
	}
}

void checkSerial(int seav){
  if (Serial.available() > seav) {
    state = Serial.read();
  }
/*  if (digitalRead(17)==HIGH) {
    state = 35;
  } */
} //Will try that when I get a button. Works ok with just a resistor.
void checkSerialCustom(int seav) {
  if (Serial.available() > seav) {
    stateCustom = Serial.read();
  }
}
