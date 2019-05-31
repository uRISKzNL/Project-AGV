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
const int trigPinV = 7;
const int echoPinV = A1;
const int trigPinL;
const int echoPinL;
const int trigPinR;
const int echoPinR;
const int ledrood = 5;
const int ledgroen = 6;

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

int pos = 0;   
int ledState = LOW;           
unsigned long previousMillis = 0;        
const long interval_red = 100; 
const long interval_US_servo = 20;
long prevtijd=0;
int servo_memory = 0;


char toestand= 'r'; 
int start_stop;
int toggle_switch;
int iterations = 4;


void setup() {
myservo.attach(9);  
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
  

start_stop= analogRead(50);
toggle_switch = digitalRead(52);


if (start_stop >= 700 && toggle_switch == 1){
   

    switch (toestand){
      
    case 'r': 

      if (afstand_voor < 9 && afstand_voor > 3  ){
          toestand = 'c';
          break;
          }
      
      if (afstand_voor > 15){    
            
            for(int x = 0; x < 200; x++) {
              
                
                motor_rechts();
                motor_links();
                afstand_voorF();
                afstand_rechtsF();
                afstand_linksF();
                ledknipper();  
                servoUS();           
                }                   
          
          } break;

        

      case 'c':
          controle(); 
          break;
 

}

  }}




  
void afstand_voorF(){

tijd_voor = voor.ping_median(iterations);
afstand_voor = (tijd_voor /2) * 0.034;
Serial.println(afstand_voor);
}

void afstand_linksF(){

tijd_links = links.ping_median(iterations);
afstand_links = (tijd_links /2) * 0.034;
Serial.println(afstand_links);
}

void afstand_rechtsF(){

tijd_rechts = rechts.ping_median(iterations);
afstand_rechts = (tijd_rechts /2) * 0.034;
Serial.println(afstand_rechts);
}


void ledknipper(){


unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval_red) {
   
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(6, ledState);
    }
}

void controle(){
  

// motoren uit
//float compdistance_voor;
//distance_voor = compdistance_voor;

  
 //for (pos = pos; pos <= 110; pos += 1) { 
  
      //distance_voor1();
      //myservo.write(pos);              
      //delay(30);
      
      
      //if (distance_voor - compdistance_voor > 1.5){

      //digitalWrite(5,HIGH); //waarschuwing  
      //}
      //}  
     //myservo.write(90);
     //toestand = 'r';              
         
     
     
     }


   
void TOFdistance(){
}

void motor_rechts(){
 digitalWrite(dirPinR,LOW); 
 
    digitalWrite(stepPinR,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(stepPinR,LOW); 
    delayMicroseconds(2000); 

}

void motor_links(){
 digitalWrite(dirPinL,LOW); 
 
    digitalWrite(stepPinL,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(stepPinL,LOW); 
    delayMicroseconds(2000); 

}

void servoUS(){

long tijd = millis();

if (tijd-prevtijd > interval_US_servo){ 

if (pos >= 179){
  
    servo_memory = 1;
}
if (pos <= 0){
  
    servo_memory = 0;
}


if (servo_memory == 1 ){
    prevtijd = tijd;
    pos--;
    myservo.write(pos);
}

if (servo_memory == 0){
    prevtijd = tijd;
    pos++;
    myservo.write(pos);
    

}}

}
      
  



