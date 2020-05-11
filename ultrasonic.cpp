#include <NewPing.h>

#include "ultrasonic.h"



int echo_trig = A2;

int MAX_DISTANCE = 200;

NewPing sonar(echo_trig, echo_trig, MAX_DISTANCE);

void ultrasonic_setup() {
  pinMode(echo_trig, OUTPUT);
}

unsigned long measure_distance() {
  
  unsigned long distance_to_obstacle;
  distance_to_obstacle = sonar.ping_cm();
  
  return  distance_to_obstacle;
}