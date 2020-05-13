#include "driver_motor.h"

int s1 = 3;
int s2 = 4;
int s3 = 2;
int s4 = 9;
int s5 = 7;
int near = 8;

//13.05
int graphic_code_LF;


void IR_senzor_setup() {
  
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(near, INPUT);
  motor_setup();
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
    if (senzor3 == 0 && senzor1 == 1 && senzor2 == 1 && senzor4 == 1 && senzor5 == 1) // only middle sensor sees the line
    {
      controlDirection(1); //forward
      graphic_code_LF = 50; //happy face graphic
    }

    if (senzor1 == 0 || senzor2 == 0) //left sensors sees the line
    {
      controlDirection(6); //tight left
      graphic_code_LF = 50; //happy face graphic
    }

    if (senzor1 == 0 && senzor2 == 0 && senzor4 == 0) //left sensors sees the line and one right sensor sees the line
    {
      controlDirection(6); //tight left
      graphic_code_LF = 50; //happy face graphic
    }

    if (senzor4 == 0 || senzor5 == 0) //right sensors sees the line
    {
      controlDirection(4); //tight right
      graphic_code_LF = 50; //happy face graphic
    }

    if (senzor4 == 0 && senzor5 == 0 && senzor2 == 0) //right sensors sees the line and one left sensor sees the line
    {
      controlDirection(4); //tight right
      graphic_code_LF = 50; //happy face graphic
    }

  }
  else
  {
    controlDirection(0); //stop
    graphic_code_LF = 70; //error sign graphic
  }


}