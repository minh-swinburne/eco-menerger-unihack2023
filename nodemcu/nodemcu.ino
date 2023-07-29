#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include<FirebaseESP8266.h>

// abc

FirebaseData firebaseData;
FirebaseData doublefbDta;
FirebaseJson json;

#define FIREBASE_HOST "https://smartelectric-d9ea5-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "NuhdP3ymbVpa7bUOm96VvQ7GKQ1vcGC4nPX7E6OB"

String dulieu;
char ssid[] = "He";    //enter your wifi name
char password[] = "123456789"; // enter your wifi password

//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);
//D4 = Rx & D3 = Tx
SoftwareSerial arduino(D4, D3);

void setup() {
  WiFi.begin(ssid, password);
  Serial.begin(9600);
  nodemcu.begin(9600);
  arduino.begin(9600);
  delay(1200);
  while (!Serial) continue;
}

void loop() {
  to_arduino();
  from_arduino();
}


void from_arduino() {
  delay(2000);
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(arduino);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

  Serial.println("JSON Object Recieved");
  Serial.print("Recieved mA1:  ");
  float mA1 = data["mA1"];
  Serial.println(mA1);
  Serial.print("Recieved mA2:  ");
  float mA2 = data["mA2"];
  Serial.println(mA2);
  Serial.println("-----------------------------------------"); 
}

void to_arduino() {
  delay(2000);
}
