#include <WiFiConfig.h>
#include <Adafruit_AHTX0.h>
#include <Wire.h>

#define I2C_SDA 6
#define I2C_SCL 7
#define lightSensor 4

Adafruit_AHTX0 aht;
sensors_event_t humidity, temp;

uint8_t receiverAddress[] = {0x34, 0xB7, 0xDA, 0xF6, 0x38, 0x38};


void setup() {
  Serial.begin(115200);

  Wire.begin(I2C_SDA, I2C_SCL);
  aht.begin();
  wifi_setup();
  peer_setup(receiverAddress);

  pinMode(lightSensor, INPUT);

}
void loop() {
  WeatherReport report;
  
  aht.getEvent(&humidity, &temp);
  report.humidity = humidity.relative_humidity;
  report.temperature = temp.temperature;
  String time;
  report.light = analogRead(lightSensor);
  if(report.light >= 100) time = "Day";
  else time = "Night";
  
  
  Serial.print("Temp: " + String(temp.temperature) + "C");
  Serial.println("");
  Serial.print("Hum: " + String(humidity.relative_humidity) + "%");
  Serial.println("");
  Serial.print("Light: " + String(time));
  Serial.println("");
  Serial.println("");

  send_report(receiverAddress, report);
  delay(500);

}
