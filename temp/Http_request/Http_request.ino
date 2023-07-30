
// Libraries for internet weather
#include <ESP8266HTTPClient.h>  // http web access library
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>  
String Location = "London";
String API_Key  = "90366e0d41ba5f0fcac7621190876245";
String lon = "";
String lat = "";
String dailyWeather[10];
WiFiClient wifiClient;

#define WIFI_SSID "He"
#define WIFI_PASSWORD "123456789"

void updateWeather();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  Serial.println("a: ");
  // put your main code here, to run repeatedly:
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
    }
  updateWeather();
  
  delay(5000);

}

void updateWeather(){
      HTTPClient http;  // declare an object of class HTTPClient
      // specify request destination    
      String request = "https://opentdb.com/api.php?amount=2&type=multiple";
      http.begin(wifiClient, request);  // !!
      int httpCode = http.GET();  // send the request
      if (httpCode > 0)  // check the returning code
      {
        String payload = http.getString();   // get the request response payload
        DynamicJsonBuffer jsonBuffer(512);
        // Parse JSON object
        JsonObject& root = jsonBuffer.parseObject(payload);
        
        int   humidity = root["response_code"];

        Serial.print("Do am la:");
        Serial.println(humidity);
        Serial.println("--------------------------");
      }
}
