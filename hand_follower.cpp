#include "driver_motor.h"

int IR_sensor_right = A6; // must use analogRead  (only for A6 & A7 pins Nano)
int IR_sensor_left = A7;  //// must use analogRead
int IR_sensor_middle = 8;

int graphic_code_HF;


void hand_follower_setup() {
  motor_setup();
  pinMode(IR_sensor_right, INPUT);
  pinMode(IR_sensor_left, INPUT);
  pinMode(IR_sensor_middle, INPUT);
  Serial.begin(9600);
}

void hand_follower() {
  
  if (analogRead(IR_sensor_right) < 500 && analogRead(IR_sensor_left) < 500 && digitalRead(IR_sensor_middle) == 1) // all sensors are seeing the hand    // IR_sensor_left && IR_sensor_right --> see the hand --> <500
  { //                 IR_sensor_middle  --> see the hand --> 1
    controlDirection(1); //forward
    graphic_code_HF = 50; //happy face graphic
    
  }
  while (analogRead(IR_sensor_right) < 500 && analogRead(IR_sensor_left) > 500) // right side sees the hand and left side no
  {
    controlDirection(4); //rotate right
    graphic_code_HF = 50; //happy face graphic
    
  }

  while (analogRead(IR_sensor_right) > 500 && analogRead(IR_sensor_left) < 500) // left side sees the hand and right side no
  {
    controlDirection(6); //rotate left
    graphic_code_HF = 50; //happy face graphic
    
  }

  if (analogRead(IR_sensor_right) > 500 && analogRead(IR_sensor_left) > 500 && digitalRead(IR_sensor_middle) == 0) // none of the sensors are seeing the hand
  {
    controlDirection(0); //stop
    graphic_code_HF = 60; //sad face graphic
    
  }
  if (digitalRead(IR_sensor_middle) == 1) // middle sensor sees the hand 
  {
    controlDirection(1); 
    graphic_code_HF = 50; //happy face graphic
  }
}