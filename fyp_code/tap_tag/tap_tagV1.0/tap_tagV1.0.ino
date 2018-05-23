//include necessary libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

//initialise libraries
WiFiClient wifiConnection;
PubSubClient mqttClient(wifiConnection);

//wifi settings
const char* wifiSsid = "TALKTALK765411";
const char* wifiPassword = "A3B9N6G9";
//setting values to connect to mobile hotspot
//const char* ssid = "";
//const char* password = "";

//mqtt settings
const char* mqttHost = "192.168.1.2";
const int mqttPort = 1883;

// MPU6050 Device Address
const uint8_t MPU6050SlaveAddress = 0x68;

// Select pins for gyro/accel 
const uint8_t scl = D6;
const uint8_t sda = D7;

//sensitivity scale provided in datasheet 
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131;

// MPU6050 configuration addresses
const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;

int16_t AccelX, AccelY, AccelZ, Temperature, GyroX, GyroY, GyroZ;

int LED = 5;
int BUTTON = 4;
int mode = 1;

String tapState = "off";
float waterUse = 0;

void setup() {
  Serial.begin(115200);
  Serial.begin(9600);
  
  Serial.print("Connecting to ");
  Serial.println(wifiSsid);

  WiFi.begin(wifiSsid, wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
      //print '.' every 0.5s
      delay(500);
      Serial.print(".");
    }

    //print that the wifi library is connected and the IP
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    mqttClient.setServer(mqttHost, mqttPort);

    mqttClient.setCallback(callback);

     while (!mqttClient.connected()) {
      Serial.print("Attempting MQTT connection...");
      if (mqttClient.connect("device1")) {
        Serial.println("connected");
      } else {
        Serial.print("failed, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" try again in one second");
        // Wait a second before retrying
        delay(1000);
      }
    }

    mqttClient.subscribe("waterUsage1");

  Wire.begin(sda, scl);
  MPU6050_Init();
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the red LED if a 1 was received as first character and turn the other leds off
  if ((char)payload[0] == '1') {
    char result[8]; // Buffer big enough for 7-character float
    dtostrf(waterUse, 6, 2, result);
    mqttClient.publish("waterUsage2",result);
  } 
}
    
void loop() {
  // put your main code here, to run repeatedly:
  mqttClient.loop();

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

  if (mode == 1) {
  Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
  if (AccelY > 5000){
    tapState = "on";
    waterUse = waterUse + 0.2;
  } else {
    tapState = "off";
  }
  Serial.print("Liters: ");
  Serial.println(waterUse);
  }
  //divScale();
  
  //dataWrite();
 
  delay(500);
}

void I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t data){
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.write(data);
  Wire.endTransmission();
}

void Read_RawValue(uint8_t deviceAddress, uint8_t regAddress){
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, (uint8_t)14);
  AccelX = (((int16_t)Wire.read()<<8) | Wire.read());
  AccelY = (((int16_t)Wire.read()<<8) | Wire.read());
  AccelZ = (((int16_t)Wire.read()<<8) | Wire.read());
  Temperature = (((int16_t)Wire.read()<<8) | Wire.read());
  GyroX = (((int16_t)Wire.read()<<8) | Wire.read());
  GyroY = (((int16_t)Wire.read()<<8) | Wire.read());
  GyroZ = (((int16_t)Wire.read()<<8) | Wire.read());
}

//configure MPU6050
void MPU6050_Init(){
  delay(150);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SMPLRT_DIV, 0x07);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_1, 0x01);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_2, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_CONFIG, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_GYRO_CONFIG, 0x00);//set +/-250 degree/second full scale
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_CONFIG, 0x00);// set +/- 2g full scale
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_FIFO_EN, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_INT_ENABLE, 0x01);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SIGNAL_PATH_RESET, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_USER_CTRL, 0x00);
}
