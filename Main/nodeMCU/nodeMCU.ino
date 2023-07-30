#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ACS712.h>
FirebaseData firebaseData1;
FirebaseData doublefbDta;
FirebaseJson json;

#define SENSOR A0
#define SOCKET 5  // D1
#define BUTTON 4  // D2

ACS712 sensor(ACS712_05B, SENSOR);

float I_temp, tong, I_TB, mA, power;

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
float lastW1 = 0.1;
float lastW2 = 0.1;
float W1 = 0.1;
float W2 = 0.1;
int c = 0;

#define FIREBASE_HOST "https://smartelectric-d9ea5-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "NuhdP3ymbVpa7bUOm96VvQ7GKQ1vcGC4nPX7E6OB"
String dulieu;
#define WIFI_SSID "Nhu Minh Plaza"            //enter your wifi name
#define WIFI_PASSWORD NULL // enter your wifi password

void setup() {
  Serial.begin(115200);
  pinMode(SOCKET, OUTPUT);
  pinMode(BUTTON, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Oke");
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  Serial.println("Waiting for server");
  while (!time(nullptr)) {
    Serial.print("#");
    delay(500);
  }
  Serial.println("Time respone is ok!");
  Serial.println("Ðảm bảo không có dòng điện di qua cảm biến trong quá trình cân bằng");
  delay(1000);
  Serial.println("Calibrating...");
  delay(200);
  sensor.calibrate();
  Serial.println("Quá trình cân bằng hoàn tất!!!");
  attachInterrupt(digitalPinToInterrupt(BUTTON),switch_socket, RISING);
}

void loop() {
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  day = p_tm->tm_mday;
  month = p_tm->tm_mon + 1;
  year = p_tm->tm_year + 1900;
  hour = p_tm->tm_hour;
  minute = p_tm->tm_min;

  measure_current();
  power = I_TB * 220;
  fullday = String(year) + "-" + String(month) + "-" + String(day) + " " + String(hour) + ":" + String(minute);

  Firebase.setDouble(firebaseData1, "/Device1/History/" + fullday + "/Value", power);
  bool switching = Firebase.getBool(firebaseData1, "/Device1/isOff");
  if (switching == digitalRead(SOCKET))  {
    switch_socket();
    switching = !switching;
    Firebase.setBool(firebaseData1, "/Device1/isOff", switching);
  }
  delay(5000);
  c++;
}

void switch_socket()  {
   if(digitalRead(SOCKET) == LOW)
  {
    digitalWrite(SOCKET, HIGH);
  }
  else
  {
    digitalWrite(SOCKET, LOW);
  }
}

void measure_current()  {
  for (int i=0; i<=100; i++)
  {
    I_temp = sensor.getCurrentAC(); //Ðo dòng AC
    //Serial.print("I = "); Serial.print(I); Serial.print("   ");
    tong = tong + I_temp;
    //Serial.print("Tong = "); Serial.println(tong);
  }
  I_TB = tong/100;
  tong = 0;
  //Serial.print("\t\t\t");
  Serial.print("I = "); Serial.print(I_TB); Serial.print("A"); Serial.print("   ");
  mA = I_TB * 1000;
Serial.print("mA = "); Serial.print(mA); Serial.println("mA");
  delay(100);
}
