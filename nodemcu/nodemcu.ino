#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include<FirebaseESP8266.h>

// def
// abc

FirebaseData firebaseData;
FirebaseData doublefbDta;
FirebaseJson json;

#define FIREBASE_HOST "https://eco-menerger-unihack2023-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "AIzaSyCD4XOn8FrLJuDBhiuOpja8KQZmJr7boBc"

String dulieu;
char ssid[] = "UniHack 2023";    //enter your wifi name
char password[] = "Tech4Env"; // enter your wifi password
float mA1, mA2;

//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);
//D4 = Rx & D3 = Tx
SoftwareSerial arduino(D4, D3);

void setup() {
  WiFi.begin(ssid, password);
  Serial.begin(9600);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  nodemcu.begin(9600);
  arduino.begin(9600);
  delay(700);
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

  while (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    Serial.print(".");
    delay(500);
    JsonObject& data = jsonBuffer.parseObject(arduino);
  }

  Serial.println("JSON Object Recieved");
  Serial.print("Recieved mA1:  ");
  mA1 = data["mA1"];
  Serial.println(mA1);
  Serial.print("Recieved mA2:  ");
  mA2 = data["mA2"];
  Serial.println(mA2);
  Serial.println("-----------------------------------------"); 
}

void to_arduino() {
  delay(2000);
}

void send_data()  {
  Firebase.setDouble(firebaseData, "/test/h",test);////test
  delay(100);
  Firebase.getDouble(doublefbDta, "/User/Age");
  Serial.print("smth: ");
  Serial.println(doublefbDta.doubleData());
  delay(100);
}
