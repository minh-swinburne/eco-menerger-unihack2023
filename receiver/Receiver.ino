//Sending Data from Arduino to NodeMCU Via Serial Communication
//NodeMCU code

//Include Lib for Arduino to Nodemcu
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include<FirebaseESP8266.h>

//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);

FirebaseData firebaseData;
FirebaseData doublefbDta;
FirebaseJson json;
#define FIREBASE_HOST "https://smartelectric-d9ea5-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "NuhdP3ymbVpa7bUOm96VvQ7GKQ1vcGC4nPX7E6OB"
String dulieu;
char* ssid = "He";    //enter your wifi name
char* password = "123456789"; // enter your wifi password
unsigned long previousMillis = 0;

void setup() {

  // Initialize Serial port
  Serial.begin(115200);
  nodemcu.begin(9600);
  while (!Serial) continue;
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  unsigned long currentMillis = millis();

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

  Serial.println("JSON Object Recieved");
  Serial.println("-----------------------------------------");
  Firebase.setDouble(firebaseData, "/Ampere/Amp1/TheValue1",data["mA1"]);
  Firebase.setDouble(firebaseData, "/Ampere/Amp2/TheValue2",data["mA2"]);
  int a = millis() - currentMillis;
  Firebase.setDouble(firebaseData, "/Ampere/Amp1/TheTime1", a);
  Firebase.setDouble(firebaseData, "/Ampere/Amp2/TheTime2", a);
}