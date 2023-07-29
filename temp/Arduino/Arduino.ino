//Arduino side code
//DHT11 Lib
#include <DHT.h>

//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(5, 6);
SoftwareSerial arduino(7, 8);

//Initialisation of DHT11 Sensor
#define DHTPIN 2
DHT dht(DHTPIN, DHT11);
float temp;
float hum;
int soil_mois;
//
//int rainPin = A0;
//int thresholdValue = 800;
//int sensorValue;

void setup() {
//  pinMode(rainPin, INPUT);
  Serial.begin(115200);

  dht.begin();
  nodemcu.begin(9600);
  arduino.begin(9600);
  delay(1000);

  Serial.println("Program started");
}

void loop() {

  to_nodemcu();
  delay(2000);
  from_nodemcu();
//  delay(2000);
}

void dht11_func() {
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("Temperature: ");
  Serial.println(temp);
}

void from_nodemcu() {
  Serial.println("datareceive starting...");
    StaticJsonBuffer<500> JsonBuffer;
    JsonObject& control = JsonBuffer.parseObject(arduino);
    
    if (control == JsonObject::invalid()) {
      Serial.println("Invalid Json Object");
      JsonBuffer.clear();
      return;
    }
     soil_mois = control["soil_moisture"];
    Serial.println("datareceive succeed");
  Serial.print("Received Soil Moisture:  ");
  Serial.println(soil_mois);
  Serial.println("-----------------------------------------"); 
}

void to_nodemcu() {
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  //Obtain Soil Moisture data
  dht11_func();

  //Assign collected data to JSON Object
  data["humidity"] = hum;
  data["temperature"] = temp;

  //Send data to NodeMCU
  data.printTo(nodemcu);
  jsonBuffer.clear();

  delay(1000);
}

//
//void yl69_func()  {
//  
//  sensorValue = analogRead(rainPin);
//  Serial.print(sensorValue);
//  if(sensorValue < thresholdValue){
//    Serial.println(" - Doesn't need watering");
//  }
//  else {
//    Serial.println(" - Time to water your plant");
//  }
//}
