#include <driver_motor.h>

void motor_setup(){
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
}

void controlDirection(int d) {
  switch(d) {
      case 0:
        // STOP Normal
        digitalWrite(a1, LOW);
        digitalWrite(a2, LOW);
        digitalWrite(b1, LOW);
        digitalWrite(b2, LOW);
        break;
      case 1:
        // Forward
        
        digitalWrite(a1, LOW);
        digitalWrite(a2, HIGH);
        digitalWrite(b1, LOW);
        digitalWrite(b2, HIGH);
        break;
     case 2:
        // Reverse
        digitalWrite(a1, HIGH);
        digitalWrite(a2, LOW);
        digitalWrite(b1, HIGH);
        digitalWrite(b2, LOW);
        break;
     case 3:
        // Wide Right
        digitalWrite(a1, LOW);
        digitalWrite(a2, HIGH);
        digitalWrite(b1, LOW);
        digitalWrite(b2, LOW);
        break;
     case 4:
        // Tight Right
        digitalWrite(a1, LOW);
        digitalWrite(a2, HIGH);
        digitalWrite(b1, HIGH);
        digitalWrite(b2, LOW);
        break;
     case 5:
        // Wide Left
        digitalWrite(a1, LOW);
        digitalWrite(a2, LOW);
        digitalWrite(b1, LOW);
        digitalWrite(b2, HIGH);
        break;
     case 6:
        // Tight Left
        digitalWrite(a1, HIGH);
        digitalWrite(a2, LOW);
        digitalWrite(b1, LOW);
        digitalWrite(b2, HIGH);
        break;
     
  }

void motor_test(){
  controlDirection(1);
  delay(2000);
   controlDirection(0);
  delay(1000);
  controlDirection(2);
  delay(1000);
  controlDirection(0);
  delay(1000);
   controlDirection(3);
  delay(1000);
  controlDirection(0);
  delay(1000);
   controlDirection(4);
  delay(1000);
  controlDirection(0);
  delay(1000);
   controlDirection(5);
  delay(1000);
  controlDirection(0);
  delay(1000);
   controlDirection(6);
  delay(1000);
  controlDirection(0);
  delay(1000);
}