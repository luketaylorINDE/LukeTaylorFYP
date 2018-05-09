// Including nessesary libraries.
//#include "I2Cdev.h" 
//#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

const int MPU6050_addr=0x68;
int16_t AccX,AccY,AccZ,Temp,GyroX,GyroY,GyroZ;

String tapState = "off";
float waterUse = 0;

int LED = 12;
int BUTTON = 4;
int mode = 1;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);
  
  if(digitalRead(BUTTON) == HIGH) {
  if (mode < 3) {
    mode++;
  } else {
    mode = 1;
   }
   if (mode == 1) {
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
   } else if (mode == 2){
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
   } else if (mode == 3){
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
   }
  }
  //Serial.println(mode);

  if (mode == 1) {
    accRead();
    //Serial.print(" || GyroX = "); Serial.println(GyroX);
    if (GyroX > 5000){
    tapState = "on";
    waterUse = waterUse + 0.2;
  } else {
    tapState = "off";
  }
  Serial.print("Liters: ");
  Serial.println(waterUse);
  delay(500);
  }

  if (mode == 2) {
    accRead();
    //Serial.print(" || GyroY = "); Serial.println(GyroY);
    if (GyroY < -5000) {
    tapState = "on";
    waterUse = waterUse + 0.2;
    } else {
      tapState = "off";
    }
    Serial.print("Liters: ");
    Serial.println(waterUse);
    delay(500);
  }
  /*accRead();
  //accWrite();
  if (GyroX > 5000){
    tapState = "on";
    waterUse = waterUse + 0.2;
  } else if (GyroY < -5000) {
    tapState = "on";
  } else {
    tapState = "off";
  }
  //Serial.println(tapState);
  Serial.print("Liters: ");
  Serial.println(waterUse);
  delay(500);*/
 }

void accRead() {
  //AccX=Wire.read()<<8|Wire.read();
  //AccY=Wire.read()<<8|Wire.read();
  //AccZ=Wire.read()<<8|Wire.read();
  //Temp=Wire.read()<<8|Wire.read();
  GyroX=Wire.read()<<8|Wire.read();
  GyroY=Wire.read()<<8|Wire.read();
  GyroZ=Wire.read()<<8|Wire.read();
}

void accWrite() {
  //Serial.print("AccX = "); Serial.print(AccX);
  //Serial.print(" || AccY = "); Serial.print(AccY);
  //Serial.print(" || AccZ = "); Serial.println(AccZ);
  //Serial.print(" || Temp = "); Serial.print(Temp/340.00+36.53);
  Serial.print(" || GyroX = "); Serial.print(GyroX);
  Serial.print(" || GyroY = "); Serial.print(GyroY);
  Serial.print(" || GyroZ = "); Serial.println(GyroZ);
}


