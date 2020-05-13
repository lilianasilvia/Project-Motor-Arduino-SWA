#include "graphics_matrix_led.h"
#include "temperature_humidity.h"
#include <Wire.h>

#define I2CAddress 8

int active_currect_mode;
int received_data[5];
int start_mode, stop_mode;

String temp, humid;

unsigned long previousTime_each_second = 0;
unsigned long previousTime_half_second = 0;
long intervall_each_second = 1000;
long intervall_half_second = 500;

void setup() {
  graphics_setup();
  Serial.begin(115200);
  temperature_humidity_setup();
  Wire.begin(4, 5); // SDA-GPIO4, SCL-GPIO5
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - previousTime_half_second >= intervall_half_second)       //each half second
  {
    request_data_from_Arduino(); // graphic for LF, graphic for OA, graphic for HF and current mode

    //update graphic on matrix_led
    for (int i = 0; i < 3; i++)
    {
      if (received_data[i] > 0)
      {
        update_matrix_led(received_data[i]);
      }
    }
    temp = temperature();
    humid = humidity();
    //send_data_to_page;  mode feedback, temperature, humidity, graphic 
    previousTime_half_second = currentTime;
  }

  if (currentTime - previousTime_each_second >= intervall_each_second)    //each second
  {
    //read data from page: mode, start, stop button
    send_data_to_Arduino(); //mode, start_mode, stop_mode

    previousTime_each_second = currentTime;
  }

}


void update_matrix_led(int data)
{
  switch (data) {
    case 10:
      graphic(left_arrow);
      break;

    case 20:
      graphic(forward_arrow);
      break;

    case 30:
      graphic(right_arrow);
      break;

    case 40:
      graphic(reverse_arrow);
      break;

    case 50:
      graphic(happy_face);
      break;

    case 60:
      graphic(sad_face);
      break;

    case 70:
      graphic(error_sign);
      break;
  }

}

void send_data_to_Arduino()
{
  Wire.beginTransmission(I2CAddress);
  Wire.write(active_currect_mode);
  Wire.write(start_mode);
  Wire.write(stop_mode);
  Wire.endTransmission();
}

void request_data_from_Arduino()
{
  Wire.requestFrom(I2CAddress, 4);
  while (!Wire.available()); //wait arduino to start sending data

  while (Wire.available())
  {
    for (int i = 0; i < 4; i++)
    {
      received_data[i] = Wire.read();
    }
  }
}
