#include "driver_motor.h"

int s1 = 3;
int s2 = 4;
int s3 = 2;
int s4 = 9;
int s5 = 7;
int near = 8;


void IR_senzor_setup() {
  
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(near, INPUT);
}

void line_follow() {
  int senzor1 = digitalRead(s1);  //with obstacle (does not sense the line) - LED OFF - 1 pin value
  int senzor2 = digitalRead(s2);  // No obstacle(senses the line) - LED ON  - 0 pin value
  int senzor3 = digitalRead(s3);
  int senzor4 = digitalRead(s4);
  int senzor5 = digitalRead(s5);
  int senzorNear = digitalRead(near);

   if (senzorNear == 0)
  {
    if (senzor3 == 0 && senzor1 == 1 && senzor2 == 1 && senzor4 == 1 && senzor5 == 1)
    {
      controlDirection(1); //forward
    }

    if (senzor2 == 0 && senzor1 == 1)
    {
      controlDirection(6); //wide left5
    }

    if (senzor1 == 0 && senzor2 == 1)
    {
      controlDirection(6); //tight left6
    }

    if (senzor1 == 0 && senzor2 == 0)
    {
      controlDirection(6); //tight left6
    }

    if (senzor1 == 0 && senzor2 == 0 && senzor4 == 0)
    {
      controlDirection(6); //tight left6
    }

    if (senzor4 == 0 && senzor5 == 1)
    {
      controlDirection(4); //wide right3
    }

    if (senzor5 == 0 && senzor4 == 1)
    {
      controlDirection(4); //tight right4
    }

    if (senzor4 == 0 && senzor5 == 0)
    {
      controlDirection(4); //tight right4
    }

    if (senzor4 == 0 && senzor5 == 0 && senzor2 == 0)
    {
      controlDirection(4); //tight right4
    }

  }
  else
  {
    controlDirection(0); //stop
  }


}

