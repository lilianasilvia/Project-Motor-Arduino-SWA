#include "line_follower.h"
#include "obstacle_avoid.h"
#include "hand_follower.h"
#include <Wire.h>

#define I2CAddress 8

int received_current_mode_wemos;
int response[5];

void setup() {
  
  obstacle_mode_setup();  //obstacle_avoid mode
  IR_senzor_setup();      //line_follower mode
  hand_follower_setup();  //hand_follower mode

  Wire.begin(I2CAddress);
  Wire.onReceive(espWifiReceiveEvent);
  Wire.onRequest(espWifiRequestEvent);
}

void loop() {

  if(received_current_mode_wemos == 1)
  {
    line_follow(); //mode 1
    
    response[3] = 1; //send feedback to wemos that the mode was updated 
    response[1] = graphic_code_LF; //send to wemos the graphic code to show on matrix led and page
    response[0] = -1; // sending -1 value to wemos will represent "ignore" value
    response[2] = -1; // sending -1 value to wemos will represent "ignore" value
  }
  if(received_current_mode_wemos == 2)
  {
    obstacle_avoid(); //mode 2

    response[3] = 2; //send feedback to wemos that the mode was updated 
    response[2] = graphic_code_OA; //send to wemos the graphic code to show on matrix led and page
    response[0] = -1; // sending -1 value to wemos will represent "ignore" value
    response[1] = -1; // sending -1 value to wemos will represent "ignore" value
  }
  if(received_current_mode_wemos == 3)
  {
    hand_follower(); //mode 3

    response[3] = 3; //send feedback to wemos that the mode was updated 
    response[0] = graphic_code_HF; //send to wemos the graphic code to show on matrix led and page
    response[1] = -1; // sending -1 value to wemos will represent "ignore" value
    response[2] = -1; // sending -1 value to wemos will represent "ignore" value
  }
  
}


void espWifiReceiveEvent(int count)
{
  //Serial.print("Received[");
  while (Wire.available())
  {
    received_current_mode_wemos = Wire.read();
    //Serial.print(received_current_mode_wemos);
  }
  //Serial.println("]");
  //calc response.
}

void espWifiRequestEvent()
{
  for(int i = 0; i < 4; i++)
  {
    Wire.write(response[i]);
  }
  //Serial.print("A venit request");
}
