#include <WiFiConfig.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


// Initialize a WeatherReport to store the values
WeatherReport report;


void setup() {
  Serial.begin(115200);
  wifi_setup();
  set_report_receiver(&report);
  lcd.init();
  lcd.backlight();
}


void loop() {
  Serial.print("Temp: " + String(report.temperature) + "C");
  Serial.println("");
  Serial.print("Hum: " + String(report.humidity) + "%");
  Serial.println("");
  Serial.print("Light: " + String(report.light));
  Serial.println("");
  Serial.println("");
  String time;
  if(report.light >= 100) time = "Day  ";
  else time = "Night  ";

  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(report.temperature) + "C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: " + String(report.humidity) + "%, " + time);

  delay(500);
}