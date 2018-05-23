//include necessary libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

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

float data;

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
  Serial.println(data);
  delay(500);
}


