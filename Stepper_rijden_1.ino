
const int stepPinR = 36; //36 
const int dirPinR = 38;  //38
const int stepPinL = 32; //36 
const int dirPinL = 28;  //38

void setup() {

 pinMode(stepPinR,OUTPUT); 
 pinMode(dirPinR,OUTPUT);
 pinMode(stepPinL,OUTPUT); 
 pinMode(dirPinL,OUTPUT);
}

void loop() {
rijden();
}

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
