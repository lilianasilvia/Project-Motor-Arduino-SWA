#include <DHT.h>

#define DHTPIN 0
#define DHTTYPE DHT22

DHT dht = DHT(DHTPIN, DHTTYPE);

void temperature_humidity_setup() {
  dht.begin();
  Serial.begin(115200);
}

String temperature() {
  float t = dht.readTemperature();
  return String(t);
}

String humidity() {
  float h = dht.readHumidity();
  return String(h);
}