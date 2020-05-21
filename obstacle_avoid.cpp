#include "driver_motor.h"
#include "ultrasonic.h"
#include <Servo.h>

Servo motor_servo;

int right_direction = 25;
int left_direction = 155;
int IR_obstacle_sensor_1 = A6;
int IR_obstacle_sensor_2 = A7;
int IR_middle_sensor = 8; //IR sensor from line follower
int straight = 85;
int servoPin = 5;
unsigned long distance_to_obstacle, distance_right, distance_left;
int graphic_code_OA;

void obstacle_mode_setup() {
  motor_servo.attach(servoPin);
  Serial.begin(9600);
  pinMode(IR_obstacle_sensor_1, INPUT);
  pinMode(IR_obstacle_sensor_2, INPUT);
  pinMode(IR_middle_sensor, INPUT);
  ultrasonic_setup();
  motor_setup();
}

void obstacle_avoid() {

  motor_servo.write(straight); // look forward

  distance_to_obstacle = measure_distance();
  Serial.println(distance_to_obstacle);



  if (analogRead(IR_obstacle_sensor_1) > 500 && analogRead(IR_obstacle_sensor_2) > 500 && digitalRead(IR_middle_sensor) == 0) //while no obstacle
  {
    controlDirection(1); //go forward
    graphic_code_OA = 20; // graphic forward arrow
  }

  else //obstacle detected
  {
    controlDirection(2); //reverse
    graphic_code_OA = 40; //graphic reverse arrow
    delay(500);

    controlDirection(0); //stop
    graphic_code_OA = 70; //graphic obstacle arrow

    motor_servo.write(right_direction);
    delay(1000);
    distance_right = measure_distance();

    motor_servo.write(left_direction);
    delay(1000);
    distance_left = measure_distance();

    motor_servo.write(straight); //come back to straight
    delay(1000);

    if (distance_right > distance_left)
    {
      controlDirection(4); //tight right
      graphic_code_OA = 30;
      delay(500);
      controlDirection(0); //stop
      delay(1000);
    }
    else
    {
      controlDirection(6); //tight left
      graphic_code_OA = 10;
      delay(500);
      controlDirection(0); //stop
      delay(1000);
    }
  }



}
