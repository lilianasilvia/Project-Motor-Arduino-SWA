#include "line_follower.h"
#include "obstacle_avoid.h"
#include "hand_follower.h"
#include "driver_motor.h"

#include <Wire.h>

#define I2CAddress 8

int received_current_mode_wemos;
int received_data_wemos;
int response[5];
int start_active = 0;
int stop_active = 0;


void setup() {
  
  obstacle_mode_setup();  //obstacle_avoid mode
  IR_senzor_setup();      //line_follower mode
  hand_follower_setup();  //hand_follower mode

  Wire.begin(I2CAddress);
  Wire.onReceive(espWifiReceiveEvent);
  Wire.onRequest(espWifiRequestEvent);
}

void loop() {

  if(received_current_mode_wemos == 1 && start_active == 100)
  {
    line_follow(); //mode 1
    
    response[3] = 1; //send feedback to wemos that the mode was updated 
    response[1] = graphic_code_LF; //send to wemos the graphic code to show on matrix led and page
    response[0] = 0; // sending 0 value to wemos will represent "ignore" value
    response[2] = 0; // sending 0 value to wemos will represent "ignore" value
  }
  if(received_current_mode_wemos == 2 && start_active == 100)
  {
    obstacle_avoid(); //mode 2

    response[3] = 2; //send feedback to wemos that the mode was updated 
    response[2] = graphic_code_OA; //send to wemos the graphic code to show on matrix led and page
    response[0] = 0; // sending 0 value to wemos will represent "ignore" value
    response[1] = 0; // sending 0 value to wemos will represent "ignore" value
  }
  if(received_current_mode_wemos == 3 && start_active == 100)
  {
    hand_follower(); //mode 3

    response[3] = 3; //send feedback to wemos that the mode was updated 
    response[0] = graphic_code_HF; //send to wemos the graphic code to show on matrix led and page
    response[1] = 0; // sending 0 value to wemos will represent "ignore" value
    response[2] = 0; // sending 0 value to wemos will represent "ignore" value
  }

  if(start_active == 0)
  {
    controlDirection(0); //stop motors
  }
  
}


void espWifiReceiveEvent(int count)
{
  //Serial.print("Received[");
  while (Wire.available())
  {
    received_data_wemos = Wire.read();

    if(received_data_wemos == 1 || received_data_wemos == 2 || received_data_wemos == 3)
    {
      received_current_mode_wemos = received_data_wemos;
      start_active = 0;
      
    }
    else if(received_data_wemos == 100)
    {
      start_active = received_data_wemos;
      stop_active = 0;
    }
    else if(received_data_wemos == 200)
    {
      stop_active = received_data_wemos;
      start_active = 0;
      
    }
  }
  
}

void espWifiRequestEvent()
{
  for(int i = 0; i < 4; i++)
  {
    Wire.write(response[i]);
  }
  
}
