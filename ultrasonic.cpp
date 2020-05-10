#include "ultrasonic.h"

int echo = A3;
int trig = A2;
float speed_of_sound;
float temp = 25;  //will be recived periodically by wemos (the pin measuring temperature will be on wemos)
long time_ultrasound_return;



void ultrasonic_setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
}

float measure_distance() {

  trigger_pulse();
  time_ultrasound_return = pulseIn(echo, HIGH);
  
  speed_of_sound = (331.3 + 0.606*temp)/10000; //result in cm/us
  
  return ((time_ultrasound_return * speed_of_sound )/2.0); //result in cm
}

void trigger_pulse()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
}
