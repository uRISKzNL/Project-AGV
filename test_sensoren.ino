#define TRIGTIME 200
#define ECHOTIME 1000


// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;
 
unsigned long time_1 = 0; 
unsigned long time_2 = 0; 

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
if(millis() > time_1 + TRIGTIME){
        time_1 = millis();
        } 

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
if(millis() > time_2 + ECHOTIME){
        time_2 = millis();
        digitalWrite(trigPin, LOW);
        }
         
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

//test aanpassing github

}
