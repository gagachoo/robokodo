#ifdef ESP32
#include <WiFi.h>
#else 
#include <ESP8266WiFi.h>
#endif
 
//  https://voltiq.ru/esp-now-esp32-arduino-ide/?ysclid=lwcj2mpm9l199316955


void setup() { 
  Serial.begin(115200);
  Serial.println(); 
  Serial.print("ESP Board MAC Address:&nbsp; "); 
  Serial.println(WiFi.macAddress());
}

void loop() {
}