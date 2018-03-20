#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

int sensorPin = A0;
int sensorValue = 0; 
float price;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
}

void loop() {
 lcd.clear();
 sensorValue = analogRead(sensorPin);
 String fRate = String (sensorValue / 100);
 price = price + fRate.toInt() * 0.003;
 Serial.println("Flow: " + fRate + " l/s");
 Serial.println("Price: £" + String(price));
 lcd.print("Flow: " + fRate + " l/s");
 lcd.setCursor(0,1);
 lcd.print("Price: " + String(price));
 delay(1000);
}



