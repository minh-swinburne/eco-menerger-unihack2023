//// cài đặt fribase
#include <ESP8266WiFi.h>
#include<FirebaseESP8266.h>
FirebaseData firebaseData;
FirebaseData doublefbDta;
FirebaseJson json;
#define FIREBASE_HOST "https://smartelectric-d9ea5-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "NuhdP3ymbVpa7bUOm96VvQ7GKQ1vcGC4nPX7E6OB"
String dulieu;
char* ssid = "He";    //enter your wifi name
char* password = "123456789"; // enter your wifi password

void setup() {
  Serial.begin(115200);

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
  int test = random(0,100);
  Firebase.setDouble(firebaseData, "/test/h",test);////test
  delay(100);
  Firebase.getDouble(doublefbDta, "/User/Age");
  Serial.print("smth: ");
  Serial.println(doublefbDta.doubleData());
  delay(100);
}

