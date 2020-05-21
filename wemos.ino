#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "index.h"

#include "graphics_matrix_led.h"
#include "temperature_humidity.h"
#include <Wire.h>

#define I2CAddress 8

//web server setup
const char* ssid = "LiliSamsung";
const char* password = "mopi9745";
ESP8266WebServer server(80);

int active_current_mode = 0;
int active_current_graphic;
int received_data[5];
int start_mode = 100, stop_mode = 200;

String temp, humid;

//unsigned long previousTime_each_second = 0;
unsigned long previousTime = 0;
//long intervall_each_second = 1000;
long intervall = 200;


void setup() {
  graphics_setup();
  Serial.begin(115200);
  temperature_humidity_setup();
  Wire.begin(4, 5); // SDA-GPIO4, SCL-GPIO5

  //wifi setup
  WiFi.begin(ssid, password);

  Serial.println("");
  Serial.print("Astept sa ma conectez ...");

  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  if ( WiFi.status() == WL_CONNECTED ) {
    // Mesaj Conectare
    Serial.println("");
    Serial.println("Wireless Conectat! ");

    // Adresa IP
    Serial.print("Adresa IP: ");
    Serial.println( WiFi.localIP() );

    server.on("/", handle_index);
    server.on("/temperature_humidity", handle_t_h);
    server.on("/get_mode", handle_get_mode);
    server.on("/get_graphic_status", handle_get_graphic_status);
    server.on("/set_mode", handle_set_mode);
    server.on("/start_set",handle_start_set);
    server.on("/stop_set",handle_stop_set);

    // start server
    server.begin();
    Serial.println("Serverul a pornit!");

  } else {
    // In caz ca nu reuseste sa se conecteze
    Serial.println("Eroare neprevazuta! Nu sunt conectat la WiFi");
  }
}

void loop() {

  server.handleClient();
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= intervall)       //each 200 ms
  {
    request_data_from_Arduino(); // graphic for LF, graphic for OA, graphic for HF and current mode

    //update graphic on matrix_led
    for (int i = 0; i < 3; i++)
    {
      if (received_data[i] > 0)
      {
        update_matrix_led(received_data[i]);
        active_current_graphic = received_data[i];
      }
    }
    temp = temperature();
    humid = humidity();
    //send_data_to_page;  mode feedback, temperature, humidity, graphic
    previousTime = currentTime;
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

void send_mode_to_Arduino()
{
  Wire.beginTransmission(I2CAddress);
  Wire.write(active_current_mode);
  Wire.endTransmission();
}

void send_start_to_Arduino()
{
  Wire.beginTransmission(I2CAddress);
  Wire.write(start_mode);
  Wire.endTransmission();
}

void send_stop_to_Arduino()
{
  Wire.beginTransmission(I2CAddress);
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
      Serial.print(received_data[i]);
      Serial.print(" ");
    }
    Serial.println("");
  }
}


void handle_index() {
  server.send(200, "text/html", PAGINA);
}

void handle_t_h() {
  server.send(200, "text/html", "Temp: " + temp + " °C / Humidity: " + humid + " %");
}

void handle_get_mode() {
  server.send(200, "text/html", String(active_current_mode));
}

void handle_get_graphic_status() {
  server.send(200, "text/html", String(active_current_graphic));
}

void handle_set_mode() {
  String new_mode = server.arg("m");
  active_current_mode = new_mode.toInt();
  // send to arduino new mode
  send_mode_to_Arduino();
}

void handle_start_set() {
  
  send_start_to_Arduino();
}

void handle_stop_set() {
  
  send_stop_to_Arduino();
}
