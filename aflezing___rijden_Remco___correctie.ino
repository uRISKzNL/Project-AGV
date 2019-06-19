#include <NewPing.h>


void setup() {
  // put your setup code here, to run once:

}

void loop() {


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
        if (distanceV < 9){
          toestand = 'c';
        }
         meet_TOF(toestand);
         pos = pos + 20;
         myservo.write(pos);
         teller1=0;
                  }
    
      if ( teller1 == 2 && Servo_mem == 1 ){
          US_voor();
          if (distanceV < 9){
          toestand = 'c';
        }
          meet_TOF(toestand);
          pos = pos - 20;
          myservo.write(pos);
          teller1=0;
  
          }

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



