#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;
Servo myservo;

const int stepPinR = 3; 
const int dirPinR = 4; 
const int stepPinL = 11; 
const int dirPinL = 12; 
const int trigPinV = A12;
const int echoPinV = A3;
const int trigPinL;
const int echoPinL;
const int trigPinR;
const int echoPinR;
const int ledrood = 40;
const int ledgroen = 42;
int teller = 0;
#define afstand_max 3000


NewPing voor(trigPinV, echoPinV, afstand_max);
NewPing links(trigPinL, echoPinL, afstand_max);
NewPing rechts(trigPinR, echoPinR, afstand_max);


float afstand_voor;
long tijd_voor;
float afstand_links;
long tijd_links;
float afstand_rechts;
long tijd_rechts;
float grootstemeetwaarde=0;
int pos = 40;   
int ledState = LOW;           
unsigned long previousMillis = 0;        
const long interval_red = 100; 
const long interval_US_servo = 20;
long prevtijd=0;
int servo_memory = 0;
float compdistance_voor ;


char toestand= 'r'; 
int start_stop;
int toggle_switch;
int iterations = 3;


void setup() {
myservo.attach(46);  
pinMode(trigPinV, OUTPUT); 
pinMode(trigPinL, OUTPUT); 
pinMode(trigPinR, OUTPUT); 
pinMode(trigPinV, INPUT); 
pinMode(trigPinL, INPUT); 
pinMode(trigPinR, INPUT);

 
pinMode(ledgroen, OUTPUT);
pinMode(ledrood, OUTPUT);

Serial.begin(9600);

pinMode(stepPinL,OUTPUT); 
pinMode(dirPinL, OUTPUT);
pinMode(stepPinR,OUTPUT); 
pinMode(dirPinR,OUTPUT);


}

void loop() {
tijd_voor = voor.ping_median(iterations);
afstand_voor = (tijd_voor /2) * 0.034;
Serial.println("   ");

Serial.println(afstand_voor);

if (afstand_voor < 9 && afstand_voor > 5){
myservo.write(90); 
delay(1000);             


// motoren uit
if (teller == 0){
compdistance_voor = afstand_voor ;
teller = 1;
}

 for (pos = 70; pos <= 110; pos += 1) { 
      afstand_voorF();
      myservo.write(pos);              
      delay(15);
      
      
      
      if (grootstemeetwaarde < afstand_voor){
        grootstemeetwaarde = afstand_voor;
      }
 }
      Serial.print(" gmw "); 
      Serial.print(grootstemeetwaarde);
      Serial.print("\t"); 
      Serial.print("comp: "); 
      Serial.print(compdistance_voor);
      Serial.print("\t   "); 
      Serial.print(" afstand voor "); 
      Serial.print(afstand_voor);
      teller=0;
      
      if ((grootstemeetwaarde - compdistance_voor) > 0.8){
      for(int x=0 ;x <6;x++){
      digitalWrite(ledrood,HIGH);
      delay(100);
      digitalWrite(ledrood,LOW);
      delay(100);
     }
     }
       if ((grootstemeetwaarde - compdistance_voor) <= 0.8){
      
      for(int x=0; x <6;x++){
      digitalWrite(ledgroen,HIGH);
      delay(100);
      digitalWrite(ledgroen,LOW);
      delay(100);
     }
      
      }
      
      delay(1000);}}


      
      
      
      
      
      
      
       



  
void afstand_voorF(){

tijd_voor = voor.ping_median(iterations);
afstand_voor = (tijd_voor /2) * 0.034;
}



void ledknipper_groen(){


unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval_red) {
   
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledgroen, ledState);
    }
}


   
void TOFdistance(){
  
}

void ledknipper_rood(){


unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval_red) {
   
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledrood, ledState);
    }}

      
  



