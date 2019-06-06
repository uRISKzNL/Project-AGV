#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;


#include <NewPing.h>


const int trigPinV = A12;
const int echoPinV = A3;
const int trigPinL = A13;
const int echoPinL = A2;
const int trigPinR = A14;
const int echoPinR = A1;
const int trigPinA = A15;
const int echoPinA = A0;

#define afstand_max 3000

NewPing voor(trigPinV, echoPinV, afstand_max);
NewPing links(trigPinL, echoPinL, afstand_max);
NewPing rechts(trigPinR, echoPinR, afstand_max);
NewPing achter(trigPinA, echoPinA, afstand_max);

float durationR;
float distanceR;
float durationL;
float distanceL;
float durationA;
float distanceA;
float durationV;
float distanceV;

int iterations = 3;
const int stepPin = 32; //36 
const int dirPin = 28;  //38
const int stepPin2 = 36; //36 
const int dirPin2 = 38;  //38 



void setup(){
  


cli();//stop interrupts



//set timer1 interrupt at 1Hz
 TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  OCR1A = 1500;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);


pinMode(trigPinV, OUTPUT); 
pinMode(echoPinV, INPUT); 
Serial.begin(9600); 
pinMode(trigPinL, OUTPUT); 
pinMode(echoPinL, INPUT); 
pinMode(trigPinR, OUTPUT); 
pinMode(echoPinR, INPUT); 
 pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);

  


sei();//allow interrupts
 }//end setup


ISR(TIMER1_COMPA_vect){
  for( int x =0 ; x < 25; x++){
  digitalWrite(dirPin,LOW); 
  digitalWrite(dirPin2,HIGH); 

  digitalWrite(stepPin,HIGH); 
    delayMicroseconds(800);
    digitalWrite(stepPin,LOW);  
    delayMicroseconds(800);
    

    digitalWrite(stepPin2,HIGH); 
    delayMicroseconds(800);
    digitalWrite(stepPin2,LOW);  
    delayMicroseconds(800); 
  }}
 





void loop(){
 

durationV = voor.ping_median(iterations);
distanceV = (durationV /2) * 0.034;
durationL = links.ping_median(iterations);
distanceL = (durationL /2) * 0.034;
durationR = rechts.ping_median(iterations);
distanceR= (durationR /2) * 0.034;

Serial.print("voor:  ");
Serial.print(distanceV);
Serial.print("\t");
Serial.print("LINKS:  ");
Serial.print(distanceL);
Serial.print("\t");
Serial.print("rechts:");
Serial.println(distanceR);
}

