#include <Servo.h>
#include <NewPing.h>

#define TRIGTIME 200
#define ECHOTIME 1000

int iterations = 3;

// defines pins numbers
const int trigPinV = A12;
const int echoPinV = A3;
const int trigPinL = A13;
const int echoPinL = A2;
const int trigPinR = A14;
const int echoPinR = A1;
const int trigPinA = A15;
const int echoPinA = A0;

Servo myservo;

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
int pos;
// defines variables
long duration;
int distance;
int range;

unsigned long time_1 = 0; 
unsigned long time_2 = 0; 

// defines stepperpin
const int stepPinR = 36; //36 
const int dirPinR = 38;  //38
const int stepPinL = 32; //36 
const int dirPinL = 28;  //38

//correctie rechts
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
  }
}

//correctie links
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
  }
}


//rijmodule
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

//rijmodule achteruit
void achterrijden(){


 digitalWrite(dirPinR,LOW); 
  digitalWrite(dirPinL,HIGH); 

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

void setup() {
//pinmodus steppers
pinMode(stepPinR,OUTPUT); 
pinMode(dirPinR,OUTPUT);
pinMode(stepPinL,OUTPUT); 
pinMode(dirPinL,OUTPUT);

//pinmodus echovoor
pinMode(trigPinV, OUTPUT); 
pinMode(echoPinV, INPUT);

//pinmodes echozijkant
pinMode(trigPinL, OUTPUT); 
pinMode(echoPinL, INPUT); 
pinMode(trigPinR, OUTPUT); 
pinMode(echoPinR, INPUT); 
//pinmodus servo 
myservo.attach(46);
Serial.begin(9600); // Starts the serial communication
}

void loop() {
durationV = voor.ping_median(iterations);
distanceV = (durationV /2) * 0.034;
durationL = links.ping_median(iterations);
distanceL = (durationL /2) * 0.034;
durationR = rechts.ping_median(iterations);
distanceR= (durationR /2) * 0.034;

//correctiestatements
if (distanceL <= 7.94 &&  distanceL >=  7.40 ){ 
  //7.94 en 7.40 
      cor_naarlinks();
    }
  
if (distanceL <= 6.90 && distanceL >= 6.60){  
  //6.60 en 6.90
      cor_naarrechts();
  
    }

if(distanceV > 6 && distanceV < 14){
  range = 0;
}

if(distanceV > 20){
  range = 1;
}


switch (range){
  case 0: //persoon voor je
  myservo.write(90);
  rijden();
  /*if(distanceL>10 && distanceV>15){
    //6cm rijden
    if(distanceV<5){
    //draaien links
    }
  }
  break;
  case 1: //persoon kwijt
  /*if(distanceL > 6 && distanceL < 14){
    //draaienlinks
  }

  myservo.write(180);
  if(distanceR > 6 && distanceR < 14){
    //draaienrechts
  }
  
  break;*/
  case 2: //persoon rechts
  break;
  
}


}
