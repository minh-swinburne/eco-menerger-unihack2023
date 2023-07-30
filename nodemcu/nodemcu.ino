#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <NTPClient.h>
#include <SoftwareSerial.h>
#include <WiFiUdp.h>
#include <Wire.h>

// Insert your network credentials
#define WIFI_SSID "UniHack 2023"
#define WIFI_PASSWORD "Tech4Env"

// Insert RTDB URLefine the RTDB URL
#define FIREBASE_HOST "https://gotchu-babi-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "pLiQSnREiaWibCedHOoAmzXJkZ1wKNr835SfaZUe"

// Define Firebase objects
FirebaseData fbdo, firebaseData1, firebaseData2;
FirebaseData firebaseSwitch1, firebaseSwitch2;
FirebaseJson json;

// Variable to save USER UID
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

  databasePath = "/UsersData/Minh/readings";
  nodemcu.begin(9600);
  arduino.begin(9600);
  delay(1000);
}

void loop() {
  to_arduino();
  from_arduino();
  upload_data();
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

    json.set(sen1Path.c_str(), String(mA1));
    json.set(sen2Path.c_str(), String(mA2));
    json.set(timePath, String(timestamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
  }
}

void from_arduino() {
  delay(1000);  
    StaticJsonBuffer<1000> jsonBuffer;
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
  
  StaticJsonBuffer<1500> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  //Assign collected data to JSON Object
  data["socket1"] = switch1;
  data["socket2"] = switch2; 

  //Send data to NodeMCU
  data.printTo(arduino);
  jsonBuffer.clear();
}
