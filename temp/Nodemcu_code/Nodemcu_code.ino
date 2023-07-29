#define BLYNK_TEMPLATE_ID "TMPL65X0FOIYR"
//#define BLYNK_DEVICE_NAME "NodeMCU"
//#define BLYNK_AUTH_TOKEN "xiQDX1Tae7mffiFcw87uwOw2zcIv7BZo"
//#define BLYNK_TEMPLATE_NAME "DHTSensor"
//#define BLYNK_PRINT Serial
////#define BLYNK_DEBUG
//
//#define APP_DEBUG
//#define USE_NODE_MCU_BOARD

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <BlynkSimpleEsp8266.h>

//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);
SoftwareSerial arduino(D4, D3);
BlynkTimer timer; //announcing the timer

float hum, temp;

int rainPin = A0;
int thresholdValue = 800;
int soil_mois;
//
//char auth[] = BLYNK_AUTH_TOKEN;
//char ssid[] = "Bamboo Green - Restaurant";
////char pass[] = "0914245091";

void from_arduino()  {
    Serial.println("datareceive starting...");
    StaticJsonBuffer<500> JsonBuffer;
    JsonObject& data = JsonBuffer.parseObject(nodemcu);
    
    if (data == JsonObject::invalid()) {
      Serial.println("Invalid Json Object");
      JsonBuffer.clear();
      return;
    }
     temp = data["temperature"];
     hum  = data["humidity"];
    Serial.println("datareceive succeed");
    Serial.print("Received Humidity:  ");
    Serial.println(hum);
    Serial.print("Received Temperature:  ");
    Serial.println(temp);
    Serial.println("-----------------------------------------"); 
}

void to_arduino() {
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& control = jsonBuffer.createObject();

  //Obtain Soil Moisture data
  yl69_func();

  //Assign collected data to JSON Object
  control["soil_moisture"] = soil_mois;

  //Send data to NodeMCU
  control.printTo(arduino);
  jsonBuffer.clear();

  delay(1000);
}

void datasend() {
  Serial.println("datasend starting...");
  Blynk.virtualWrite(V1,temp);
  Blynk.virtualWrite(V2,hum);
  Blynk.virtualWrite(V3,soil_mois);
  Blynk.virtualWrite(V4, millis()/1000);
  Serial.print("Received Humidity:  ");
  Serial.println(hum);
  Serial.print("Received Temperature:  ");
  Serial.println(temp);
  Serial.print("Received Soil Moisture:  ");
  Serial.println(soil_mois);
  Serial.println("datasend succeed");
  Serial.println("-----------------------------------------"); 
}

void setup() {
  
  pinMode(rainPin, INPUT);
  // Initialize Serial port
//  WiFi.begin(ssid);
  Serial.begin(115200);
  nodemcu.begin(9600);
  arduino.begin(9600);
//  timer.setInterval(1000L, datareceive);
//  timer.setInterval(2000L, datasend);
  delay(1000);
}

void loop() {
  delay(2000);
  from_arduino();
//  delay(2000);
  to_arduino();
//  Blynk.begin(auth, ssid, NULL);
//  delay(500);
//  Blynk.run();
//  delay(500);
//  datasend();
//  Blynk.disconnect();
}

void yl69_func()  {
  
  soil_mois = analogRead(rainPin);
  Serial.print(soil_mois);
  if(soil_mois < thresholdValue){
    Serial.println(" - Doesn't need watering");
  }
  else {
    Serial.println(" - Time to water your plant");
  }
}
