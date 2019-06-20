
#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;
#include <NewPing.h>
#include <Servo.h>
Servo myservo;

const int trigPinV = A12;
const int echoPinV = A3;
const int trigPinL = A13;
const int echoPinL = A2;
const int trigPinR = A14;
const int echoPinR = A1;
const int trigPinA = A15;
const int echoPinA = A0;



float durationR;
float distanceR;
float durationL;
float distanceL;
float durationA;
float distanceA;
float durationV;
float distanceV;

#define afstand_max 3000
int iterations = 3;
int Servo_mem=0;
NewPing voor(trigPinV, echoPinV, afstand_max);
NewPing links(trigPinL, echoPinL, afstand_max);
NewPing rechts(trigPinR, echoPinR, afstand_max);
NewPing achter(trigPinA, echoPinA, afstand_max);

const int stepPin = 32; //36 
const int dirPin = 28;  //38
const int stepPin2 = 36; //36 
const int dirPin2 = 38;  //38 
long teller=0;
long teller1=0;

int pos = 40;
void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif

pinMode(trigPinV, OUTPUT); 
pinMode(echoPinV, INPUT); 
pinMode(trigPinL, OUTPUT); 
pinMode(echoPinL, INPUT); 
pinMode(trigPinR, OUTPUT); 
pinMode(echoPinR, INPUT);


 pinMode(stepPin,OUTPUT); 
 pinMode(dirPin,OUTPUT);
 pinMode(stepPin2,OUTPUT); 
pinMode(dirPin2,OUTPUT);

  
}


void loop()
{
   teller++;
   teller1++;
   
   if (pos >= 125){
   Servo_mem = 1;
   }
   if (pos <= 61){
   Servo_mem = 0;
   }

rijden();

 if (distanceL <= 7.94 &&  distanceL >=  7.40 ){ 
  //7.94 en 7.40 
      cor_naarlinks();

  }

  if (distanceL <= 6.90 && distanceL >= 6.60){  
      //6.60 en 6.90
       cor_naarrechts();

  }
  
    

   if (teller == 4){
    US_links();
    teller = 0;
   }
        
   
    if( teller1 == 2 && Servo_mem == 0 ){
         meet_TOF();
         pos = pos + 20;
         teller1=0;
         US_voor();
                  }
    
    if ( teller1 == 2 && Servo_mem == 1 ){
        US_voor();
        meet_TOF();
        pos = pos - 20;
       teller1=0;

        }}



void meet_TOF(){
 //Serial.print("  TOF      ");


//Serial.print(sensor.readRangeSingleMillimeters());
//  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

 // Serial.println();
  
}
void US_links(){

durationL = links.ping_median(iterations);
distanceL= (durationL /2) * 0.034;
Serial.println("links:");
Serial.print(distanceL);

}

void cor_naarrechts(){

 digitalWrite(dirPin,LOW); 
  digitalWrite(dirPin2,HIGH); 
  
for( int x = 0 ;x < 6; x++){
  
digitalWrite(stepPin,HIGH); 
delayMicroseconds(1000); //1000
digitalWrite(stepPin2,HIGH);
delayMicroseconds(4000); // 2800
digitalWrite(stepPin,LOW);  
delayMicroseconds(1000); //1600
digitalWrite(stepPin2,LOW);  
delayMicroseconds(4000); //2400
}}

void US_voor(){
durationV = voor.ping_median(iterations);
distanceV = (durationV /2) * 0.034;

Serial.print("\t");
//Serial.print("voor:  ");
//Serial.print(distanceV);
}
void cor_naarlinks(){
  digitalWrite(dirPin,LOW); 
  digitalWrite(dirPin2,HIGH); 
for( int x = 0 ;x < 6; x++){
digitalWrite(stepPin,HIGH); 
delayMicroseconds(4000); //1000
digitalWrite(stepPin2,HIGH);
delayMicroseconds(1000); // 2800
digitalWrite(stepPin,LOW);  
delayMicroseconds(4000); //1600
digitalWrite(stepPin2,LOW);  
delayMicroseconds(1000); //2400
}}

void rijden(){
  
  
for( int x = 0 ;x < 20; x++){
digitalWrite(stepPin,HIGH); 
delayMicroseconds(1000); //1000
digitalWrite(stepPin2,HIGH);
delayMicroseconds(2800); // 2800
digitalWrite(stepPin,LOW);  
delayMicroseconds(1600); //1600
digitalWrite(stepPin2,LOW);  
delayMicroseconds(2400); //2400
}}

  



