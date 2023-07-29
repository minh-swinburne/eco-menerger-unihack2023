// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPL65X0FOIYR"
#define BLYNK_TEMPLATE_NAME "DHTSensor"
#define BLYNK_AUTH_TOKEN "F4PLl_1BjgRMGMRDb9tryterJ3e2N38E"

#define BLYNK_DEVICE_NAME "DHT11"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
#define USE_NODE_MCU_BOARD
#include "BlynkEdgent.h"
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
unsigned long times = millis();

#define LED 12 //D6
#define button 4 //D2
boolean btn_state = HIGH;

WidgetLED led_connect(V0);
BlynkTimer timer;

// V0 LED Widget is blinking
void blinkLedWidget(){
  if (led_connect.getValue()) {
    led_connect.off();
  } else {
    led_connect.on();
  }
}

void setup(){
  Serial.begin(115200);
  delay(100);
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  BlynkEdgent.begin();
  dht.begin();
  timer.setInterval(1000L, blinkLedWidget);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
  if(millis()-times>2000){
    // Reading temperature or humidity
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    Blynk.virtualWrite(V1,t);
    Blynk.virtualWrite(V2,h);
    Blynk.virtualWrite(V4, millis()/1000);
    if (led_connect.getValue()){
      led_connect.off();
    }else {
      led_connect.on();
    }
    Serial.print(F("Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.println(F("%"));
    times = millis();
  }
  check_button();
}

BLYNK_WRITE(V3){
  int p = param.asInt();
  digitalWrite(LED, p); 
}

void check_button(){
  if(digitalRead(button)==LOW){
    if(btn_state==HIGH){
      digitalWrite(LED,!digitalRead(LED));
      Blynk.virtualWrite(V3,digitalRead(LED));
      btn_state=LOW;
      delay(200);
    }
  }else{
    btn_state=HIGH;
  }
}
