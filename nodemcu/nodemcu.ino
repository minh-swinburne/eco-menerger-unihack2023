#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
//#include <Firebase_ESP_Client.h>
#include <FirebaseESP8266.h>
#include <NTPClient.h>
#include <SoftwareSerial.h>
#include <WiFiUdp.h>
#include <Wire.h>

// Insert your network credentials
#define WIFI_SSID "UniHack 2023"
#define WIFI_PASSWORD "Tech4Env"

// Insert RTDB URLefine the RTDB URL
#define FIREBASE_HOST "https://eco-menerger-unihack2023-default-rtdb.asia-southeast1.firebasedatabase.app/"
// Insert Firebase project API Key
#define FIREBASE_AUTH "AIzaSyCD4XOn8FrLJuDBhiuOpja8KQZmJr7boBc"

// Define Firebase objects
FirebaseData fbdo, firebaseData1, firebaseData2;
FirebaseData doublefbDta, firebaseSwitch1, firebaseSwitch2;
FirebaseJson json;

// Variable to save USER UID
String uid;
String databasePath;
String sen1Path = "/sensor1";
String sen2Path = "/sensor2";
String timePath = "/timestamp";
String parentPath;


// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Variable to save current epoch time
int timestamp;

// Timer variables (send new readings every three minutes)
unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 300000;

float mA1, mA2;

//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);
//D1 = Rx & D0 = Tx
SoftwareSerial arduino(D1, D0);

// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Function that gets current epoch time
unsigned long getTime() {
  timeClient.update();
  unsigned long now = timeClient.getEpochTime();
  return now;
}

void setup() {
  Serial.begin(9600);
  initWiFi();
  timeClient.begin();

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  databasePath = "/UsersData/Current/readings";
  
  nodemcu.begin(9600);
  arduino.begin(9600);
  while (!Serial) continue;
}

void loop() {
  to_arduino();
  from_arduino();
  upload_data();
  Firebase.getDouble(doublefbDta, "/data");
  Serial.print("smth: ");
  Serial.println(doublefbDta.doubleData());
}

void upload_data()  {
  // Send new readings to database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    //Get current timestamp
    timestamp = getTime();
    Serial.print ("time: ");
    Serial.println (timestamp);

    parentPath= databasePath + "/" + String(timestamp);

    Firebase.setDouble(firebaseData1, parentPath + sen1Path, mA1);
//    Firebase.setDouble(firebaseData2, parentPath + sen2Path, mA2);
    json.set(sen2Path.c_str(), String(mA2));
    json.set(timePath, String(timestamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
  }
}

void from_arduino() {
  char json[] = "{\"nodemcu\":{}}";
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  if (root.containsKey("nodemcu")) {
    StaticJsonBuffer<500> jsonBuffer;
    JsonObject& data = jsonBuffer.parseObject(nodemcu);
  
    if (data == JsonObject::invalid()) {
      Serial.println("Invalid Json Object");
      jsonBuffer.clear();
      return;
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
}

void to_arduino() {
  String path1 = "/data1";
  String path2 = "/data2";
  Firebase.getDouble(firebaseData1, path1.c_str());
  Serial.print("Socket 1: ");
  int switch1 = firebaseData1.doubleData();
  Serial.println(switch1);
  Firebase.getDouble(firebaseData2, path2.c_str());
  Serial.print("Socket 2: ");
  int switch2 = firebaseData2.doubleData();
  Serial.println(switch2);
  
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  //Assign collected data to JSON Object
  data["socket1"] = switch1;
  data["socket2"] = switch2; 

  //Send data to NodeMCU
  data.printTo(arduino);
  jsonBuffer.clear();
}
