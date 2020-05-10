#include "driver_motor.h"

int b1 = 12;
int b2 = A0;
int a1 = 13;
int a2 = A1;
int enB = 6; //PWM
int enA = 11; //PWM
int motor_speed_limit = 70;

void motor_setup() {
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
}

void controlDirection(int d) {
  switch (d) {
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
      analogWrite(enA, motor_speed_limit);
      analogWrite(enB, motor_speed_limit);
      break;

    case 2:
      // Reverse
      digitalWrite(a1, HIGH);
      digitalWrite(a2, LOW);
      digitalWrite(b1, HIGH);
      digitalWrite(b2, LOW);
      analogWrite(enA, motor_speed_limit);
      analogWrite(enB, motor_speed_limit);
      break;

    case 3:
      // Wide Right
      digitalWrite(a1, LOW);
      digitalWrite(a2, HIGH);
      digitalWrite(b1, LOW);
      digitalWrite(b2, HIGH);
      analogWrite(enA, motor_speed_limit);
      analogWrite(enB,0);
      break;

    case 4:
      // Tight Right
      digitalWrite(a1, LOW);
      digitalWrite(a2, HIGH);
      digitalWrite(b1, HIGH);
      digitalWrite(b2, LOW);
      analogWrite(enA, motor_speed_limit);
      analogWrite(enB, motor_speed_limit);
      break;

    case 5:
      // Wide Left
      digitalWrite(a1, LOW);
      digitalWrite(a2, HIGH);
      digitalWrite(b1, LOW);
      digitalWrite(b2, HIGH);
      analogWrite(enB, motor_speed_limit);
      analogWrite(enA, 0);
      break;

    case 6:
      // Tight Left
      digitalWrite(a1, HIGH);
      digitalWrite(a2, LOW);
      digitalWrite(b1, LOW);
      digitalWrite(b2, HIGH);
      analogWrite(enA, motor_speed_limit);
      analogWrite(enB, motor_speed_limit);
      break;

  }
}

void motor_test() {
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