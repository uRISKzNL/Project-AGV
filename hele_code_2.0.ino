#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;
Servo myservo;

const int z1 = 9;
const int z2 = 9;
const int z3 = 9;
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
long prevtijd_c=0;
#define afstand_max 3000
const int minimum_distance = 40;
const int maximum_distance = 140;

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
int ledState_red = LOW;           
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
      afstand_voorF();
      
      if (afstand_voor < z1 && afstand_voor > 3  ){
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
                ledknipper_red();  
                servoUS(); 

                if (afstand_voor < 9 && afstand_voor > 3  ){
                toestand = 'c';
                break;
                }
                //if (afstand_voor < 100 &&  ){
                 // toestand = 'b';
                //}
                
                
                }                   
          
          } break;

        

      case 'c':
          toestand = controle(pos,toestand); 
          break;

      case 'w': 
      waarschuwen();
      break;
      
      case 'b':
     

      if (afstand_links > z1  && afstand_rechts < z2 && afstand_voor < z1 ){ // bocht 1
      bocht_links_90();
      toestand = 'r';
      }
      
       

      
// switch case
    }
// knoppen
}

// loop
}




  
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


void ledknipper_red(){


unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval_red) {
   
    previousMillis = currentMillis;
    if (ledState_red == LOW) {
      ledState_red = HIGH;
    } else {
      ledState_red = LOW;
    }
    digitalWrite(6, ledState_red);
    }
}

char controle(int pos_c, char toestand_c){
  

motoren_uit();
float compafstand_voor;
int pos_c2;
afstand_voor = compafstand_voor;
pos_c =  pos_c2;
int mem0 = 2;
int mem1 = 2;

long tijd_c = millis();

if (tijd_c-prevtijd_c > interval_US_servo){ 

        if ((afstand_voor - compafstand_voor) >= 1.5 && mem0 == 1 && mem1 == 1){
        toestand_c = 'w';
        mem0=0;
        mem1=0;
        return toestand_c;
        exit(1);
        } 
        
        if ((afstand_voor - compafstand_voor) < 1.5 && mem0 == 1 && mem1 == 1){
        toestand_c = 'b';
        mem0=0;
        mem1=0;
        return toestand_c;
        exit(1);
        } 

        if (pos_c >= maximum_distance){
          
            servo_memory = 1;
            mem1=1;
        }
        if (pos_c <= minimum_distance){
          
            servo_memory = 0;
            mem0=1;
        
        }
        
        
        if (servo_memory == 1 ){
            prevtijd_c = tijd_c;
            pos_c--;
            myservo.write(pos_c);
        }
        
        if (servo_memory == 0){
            prevtijd_c = tijd_c;
            pos_c++;
            myservo.write(pos_c);
            
        
        }}
        
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

if (pos >= maximum_distance){
  
    servo_memory = 1;
}
if (pos <= minimum_distance){
  
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

void motoren_uit(){
digitalWrite(stepPinL,LOW); 
digitalWrite(stepPinR,LOW); 
}

void bocht_links_90(){

 
}

void bocht_rechts_90(){
  
} 

void waarschuwen(){
 long ledtijd = millis();
      ledknipper_red;
      if (ledtijd > 4000){
      toestand = 'c';
      }
}


