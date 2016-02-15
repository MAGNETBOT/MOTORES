// Código de prueba del servo frontal del magnetBot.
// Hecho por Roboteam, febrero 14, 2016. 

#include <Servo.h>
#define servoPin 12
Servo myservo;
int pos=0;

void setup() {
  myservo.attach(servoPin);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 30) { 
    myservo.write(pos);             
    delay(150);                      
  }
  for (pos = 180; pos >= 0; pos -= 30) { 
    myservo.write(pos);              
    delay(150);                       
  }

}
