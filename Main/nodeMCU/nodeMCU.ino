// This is for nodemcu

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

SoftwareSerial nodemcu(D6, D5);

FirebaseData firebaseData;
FirebaseData doublefbDta;
FirebaseJson json;

int day = 0;
int month = 0;
int year = 0;
int hour = 0;
int minute = 0;
String fullday = "";
int timezone = 7 * 3600;
int dst = 0;
int ngay = 0;
unsigned int t = 0;
int count = 0;
float lastW1 = 0;
float lastW2 = 0;
float W1 = 0;
float W2 = 0;


#define FIREBASE_HOST "https://smartelectric-d9ea5-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "NuhdP3ymbVpa7bUOm96VvQ7GKQ1vcGC4nPX7E6OB"
String dulieu;
char* ssid = "UniHack 2023";             //enter your wifi name
char* password = "Tech4Env";  // enter your wifi password

void setup() {
  Serial.begin(115200);
  nodemcu.begin(9600);
  while (!Serial) continue;

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Oke");
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  // Serial.println("Waiting for server");
  // while (!time(nullptr)) {
  //   Serial.print("#");
  //   delay(500);
  // }
  // Serial.println("Time respone is ok!");
}

void loop() {
  // Serial.print("sdagasdgf");

  // time_t now = time(nullptr);
  // struct tm* p_tm = localtime(&now);
  // day = p_tm->tm_mday;
  // month = p_tm->tm_mon + 1;
  // year = p_tm->tm_year + 1900;
  // hour = p_tm->tm_hour;
  // minute = p_tm->tm_min;

  //   if (year >= 2023) {
  //   if (1 < minute && minute <= 30) {
  //     fullday = String(year) + "-" + String(month) + "-" + String(day) + " " + String(hour) + ":" + 30;
  //   } else {
  //     if (minute == 0) {
  //       fullday = String(year) + "-" + String(month) + "-" + String(day) + " " + String(hour) + ":" + 00;
  //     } else {
  //       fullday = String(year) + "-" + String(month) + "-" + String(day) + " " + String((hour - 1)) + ":" + 00;
  //     }
  //   }
  // }


  // put your main code here, to run repeatedly:
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

  Serial.print("The A1: ");
  Serial.println(data["mA1"]);

  // W1 = ((atof(data["mA1"]) * 220) + lastW1 * count) / (count + 1);
  // W2 = ((atof(data["mA2"]) * 220) + lastW2 * count) / (count + 1);

  // Serial.println("/Device1/History/" + fullday + "/Value");

  //Firebase.setDouble(firebaseData, "/Device1/History/" + fullday + "/Value", W1);
  // Firebase.setString(firebaseData, "/Device1/History/" + fullday + "/date", fullday);

  // Firebase.setDouble(firebaseData, "/Device2/History/" + fullday + "/Value", W2);
  // Firebase.setString(firebaseData, "/Device2/History/" + fullday + "/date", fullday);

  // Firebase.setInt(firebaseData, "/Device1/History/" + fullday + "/Count", count + 1);

  // lastW1 = Firebase.getDouble(firebaseData, "/Device1/History/" + fullday + "/Value");
  // lastW2 = Firebase.getDouble(firebaseData, "/Device2/History/" + fullday + "/Value");
  // count = Firebase.getInt(firebaseData, "/Device2/History/" + fullday + "/Count");
}
