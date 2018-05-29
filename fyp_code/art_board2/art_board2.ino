//include necessary libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>

//initialise libraries
WiFiClient wifiConnection;
PubSubClient mqttClient(wifiConnection);

//wifi settings
//const char* wifiSsid = "TALKTALK765411";
//const char* wifiPassword = "A3B9N6G9";
//setting values to connect to mobile hotspot
//const char* wifiSsid = "Luke's iPhone";
//const char* wifiPassword = "luket9632";
//uni wifi
const char*  wifiSsid = "TP-LINK";
const char* wifiPassword = "84478221";

//mqtt settings
const int mqttPort = 1883;
//home
//const char* mqttHost = "192.168.1.12";
//home laptop
//const char* mqttHost = "192.168.1.6";
//uni tp-link
const char* mqttHost = "192.168.1.100";


float data;
#define PIN 4
uint8_t NUMPIXELS = 54;
      
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

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
      if (mqttClient.connect("device2")) {
        Serial.println("connected");
      } else {
        Serial.print("failed, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" try again in one second");
        // Wait a second before retrying
        delay(1000);
      }
    }

    mqttClient.subscribe("waterUsage3");
    
  strip.begin();
  strip.show();
  strip.setBrightness(255);

}

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
     payload[length] = '\0';
     String s = String((char*)payload);
      data = s.toFloat();
      
    
  }

  Serial.println();

  // Switch on the red LED if a 1 was received as first character and turn the other leds off
  /*if ((char)payload[0] == '1') {
    char result[8]; // Buffer big enough for 7-character float
    dtostrf(waterUse, 6, 2, result);
    mqttClient.publish("waterUsage2",result);
  }*/
}
    
void loop() {
  // put your main code here, to run repeatedly:
  mqttClient.loop();
  //Serial.println(data);
  //delay(500);
  if(data < 12.5  ) {
  loop1();
 }
 
 if(data > 12.5 && data <= 25 ) {
  loop2();
 }

 if(data > 25 && data <= 37.5 ) {
  loop3();
 }

 if(data > 37.5 && data <= 50 ) {
  loop4();
 }

 if(data > 50 && data <= 62.5 ) {
  loop5();
 }

 if(data > 62.5 && data <= 75 ) {
  loop6();
 }

 if(data > 75 && data <= 87.5 ) {
  loop7();
 }

 if(data > 87.5 && data <= 100 ) {
  loop8();
 }

 if(data > 100) {
  loop9();
 }
}

void loop1() {
  
  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 00, 255));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 51, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 51, 204));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(51, 0, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(51, 0, 204));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 102, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 102, 204));
    strip.show();
    delay(35);
  }
  
}

void loop2() {

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(51, 0, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(51, 0, 204));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(153, 0, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(153, 0, 204));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(102, 0, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(102, 0, 204));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 0, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 0, 204));
    strip.show();
    delay(35);
  }
  
}

void loop3() {

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(102, 0, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(102, 0, 204));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 0, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 0, 204));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(153, 0, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(153, 0, 204));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 0, 153));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 0, 153));
    strip.show();
    delay(35);
  }
  
}

void loop4() {

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(153, 0, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(153, 0, 204));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 0, 153));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 0, 153));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 0, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 0, 204));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 0, 102));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 0, 102));
    strip.show();
    delay(35);
  }
  
}

void loop5() {

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 0, 204));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 0, 204));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 0, 102));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 0, 102));
    strip.show();
    delay(35);
  }

    for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 0, 153));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 0, 153));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 0, 51));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 0, 51));
    strip.show();
    delay(35);
  }
  
}

void loop6() {

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 102, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 102, 0));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 204, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 204, 0));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 153, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 153, 0));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(153, 204, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(153, 204, 0));
    strip.show();
    delay(35);
  }
  
}

void loop7() {

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(204, 153, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(204, 153, 0));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(51, 204, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(51, 204, 0));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(102, 204, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(102, 204, 0));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 204, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 204, 0));
    strip.show();
    delay(35);
  }
  
}

void loop8() {

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 255, 0));
    strip.show();
    delay(35);
  }

   for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 0, 0));
    strip.show();
    delay(35);
  }

   for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 255, 0));
    strip.show();
    delay(35);
  }

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 0, 0));
    strip.show();
    delay(35);
  }
  
}
void loop9() {

  for (int i = NUMPIXELS / 2; i >= 0; i--) {
    //for (int i = 0; i < (NUMPIXELS / 2) + 1; i++) { 
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(NUMPIXELS - i, strip.Color(0, 0, 0));
    strip.show();
    delay(35);
  }
  
}

