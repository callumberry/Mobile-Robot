#include <Servo.h>

Servo servo; 


const int SERVO_PIN = 15;  

int pos = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(1000); 
  digitalWrite(LED_BUILTIN, LOW); 

  servo.attach(SERVO_PIN, 544, 2500); 



}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { 
    servo.write(pos);    
    delay(15);                       
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    servo.write(pos);      
    delay(15);                     
  }
}
