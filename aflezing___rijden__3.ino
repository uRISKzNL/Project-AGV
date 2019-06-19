
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

const int stepPinR = 36; //36 
const int dirPinR = 38;  //38
const int stepPinL = 32; //36 
const int dirPinL = 28;  //38
long teller=0;
long teller1=0;
char toestand = 'r';
int pos = 40;
long teller_TOF=0;
const int ledrood = 40;
const int ledgroen = 42;
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


 pinMode(stepPinR,OUTPUT); 
  pinMode(dirPinR,OUTPUT);
  pinMode(stepPinL,OUTPUT); 
 pinMode(dirPinL,OUTPUT);
 pinMode(ledgroen,OUTPUT);

myservo.attach(46);

  
}


void loop()
{

switch( toestand){

  
case 'r' : 
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
        US_voor();
         meet_TOF(toestand);
         pos = pos + 20;
         myservo.write(pos);
         teller1=0;
                  }
    
      if ( teller1 == 2 && Servo_mem == 1 ){
          US_voor();
          meet_TOF(toestand);
          pos = pos - 20;
          myservo.write(pos);
          teller1=0;
  
          }break;

  case 'T':

digitalWrite(dirPinR,HIGH); 
digitalWrite(dirPinL,LOW); 
 for(int x = 0; x < 150; x++) {
  
   digitalWrite(stepPinR,HIGH); 
   delayMicroseconds(3350);
   digitalWrite(stepPinL,HIGH);
   delayMicroseconds(1860);
    
    digitalWrite(stepPinL,LOW);  
    delayMicroseconds(1660);


    digitalWrite(stepPinR,LOW);  
    delayMicroseconds(3350);
  }
for (int x = 0 ; x <6; x++){
digitalWrite(ledgroen,HIGH);
delay(100);
digitalWrite(ledgroen,LOW);
delay(100);

}
 

toestand = 'r';


break;

  
          }
          
          
          
          }



long meet_TOF(char toestand_TOF){
 Serial.print("  TOF      ");


Serial.print(sensor.readRangeSingleMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

 Serial.println();
 if ( sensor.readRangeSingleMillimeters() < 200 && sensor.readRangeSingleMillimeters() > 3){

  toestand = 'T';
Serial.println("bboeeoeooeoebe");
Serial.print(toestand_TOF);

  return toestand_TOF;
 }
 
  
}


void US_links(){

durationL = links.ping_median(iterations);
distanceL= (durationL /2) * 0.034;
Serial.println("links:");
Serial.print(distanceL);

}

void cor_naarlinks(){

 delay(10);
  
for( int x = 0 ;x < 6; x++){
  

digitalWrite(stepPinL,HIGH);
delayMicroseconds(1000); // 2800
digitalWrite(stepPinR,HIGH);
delayMicroseconds(5000); // 2800

digitalWrite(stepPinL,LOW);  
delayMicroseconds(1000); //2400
digitalWrite(stepPinR,LOW);
delayMicroseconds(5000); // 2800
}}

void US_voor(){
durationV = voor.ping_median(iterations);
distanceV = (durationV /2) * 0.034;

Serial.print("\t");
Serial.print("voor:  ");
Serial.println(distanceV);

 }
void cor_naarrechts(){
  delay(10);
   
for( int x = 0 ;x < 6; x++){
digitalWrite(stepPinR,HIGH);
delayMicroseconds(5000); // 2800

digitalWrite(stepPinL,HIGH);
delayMicroseconds(1000); // 2800

digitalWrite(stepPinR,LOW);  
delayMicroseconds(5000); //2400
digitalWrite(stepPinL,LOW);  
delayMicroseconds(1000); //2400

}}

void rijden(){


 digitalWrite(dirPinR,HIGH); 
  digitalWrite(dirPinL,LOW); 

  for(int x = 0; x < 20; x++) {
  
   digitalWrite(stepPinR,HIGH); 
   delayMicroseconds(3350);
   digitalWrite(stepPinL,HIGH);
   delayMicroseconds(1860);
    
    digitalWrite(stepPinL,LOW);  
    delayMicroseconds(1660);


    digitalWrite(stepPinR,LOW);  
    delayMicroseconds(3350);
  }
}



