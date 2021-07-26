#include <Ethernet.h>
intcalibrationTime = 30;
longunsigned intlowIn;
longunsigned intpause = 5000;
boolean lockLow = true;
boolean takeLowTime;
intpirPin = 12; 
intledPin = 13;
voidsetup(){

Serial.begin(9600);

pinMode(pirPin, INPUT);

pinMode(ledPin, OUTPUT);

digitalWrite(pirPin, LOW);

//give the sensor some time to calibrate

Serial.print("calibrating sensor ");

for(inti = 0; i < calibrationTime; i++){

Serial.print(".");

delay(1000);

}

Serial.println("YES");

Serial.println("SENSOR ACTIVE");

delay(50);

}

//LOOP

voidloop(){

if(digitalRead(pirPin) == HIGH){

digitalWrite(ledPin, HIGH); //the led visualizes the sensors output pin state

if(lockLow){

lockLow = false;

Serial.println("---");

Serial.print("motion detected at ");

Serial.print(millis()/1000);

Serial.println(" sec");

delay(50);

}

takeLowTime = true;

}

if(digitalRead(pirPin) == LOW){

digitalWrite(ledPin, LOW); //the led visualizes the sensors output pin state

if(takeLowTime){

lowIn = millis(); //save the time of the transition from high to LOW

takeLowTime = false;

}

//if the sensor is low for more than the given pause,

//we assume that no more motion is going to happen

if(!lockLow && millis() - lowIn > pause){

//makes sure this block of code is only executed again after

//a new motion sequence has been detected

lockLow = true;

Serial.print("motion ended at "); //output

Serial.print((millis() - pause)/1000);

Serial.println(" sec");

delay(50);

}

}

}
