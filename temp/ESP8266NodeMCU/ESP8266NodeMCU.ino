//www.edisonsciencecorner.blogspot.com
//https://www.youtube.com/channel/UCESZHuYTzx0Eyd3yJ8u60Fg


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPL6kK_uTyq8"
#define BLYNK_TEMPLATE_NAME "testtt"
#define BLYNK_AUTH_TOKEN "m_TE_WWzWBhBDArcEdhxR68-DtDb_Kh2"

char auth[] = "m_TE_WWzWBhBDArcEdhxR68-DtDb_Kh2"; // blynk token

char ssid[] = "He";   //ssid//password
char pass[] = "123456789";    //password

int readD1;
int readD2;
int Pin_D1 = 4;
int Pin_D2 = 5;

void setup() { 
  Serial.begin(9600);
  pinMode(Pin_D1,OUTPUT);
  pinMode(Pin_D2,OUTPUT);
  pinMode(A0,INPUT);
  Blynk.begin(auth, ssid, pass);
  
}

void loop() {
  
  Blynk.run();
  
  //for first sensor
  digitalWrite(Pin_D1, HIGH);     //Turn D1 On
  delay(100);                     
  readD1 = analogRead(0);       //Read Analog value of first sensor
  digitalWrite(Pin_D1, LOW);      //Turn D1 Off
  delay(100);   
 //for second sensor
  digitalWrite(Pin_D2, HIGH);     //Turn D2 On
  delay(100);                     
  readD2 = analogRead(0);       //Read Analog value of second sensor
  digitalWrite(Pin_D2, LOW);      //Turn D2 Off
  delay(100);                     
  
  //to the serial monitor
  Serial.print("sensor 1 = ");   
  Serial.print(readD1);
  Serial.print(" / sensor 2 = ");   
  Serial.println(readD2);

  Blynk.virtualWrite(V5, readD1);  // to Blynk server
  Blynk.virtualWrite(V6, readD2);  // to Blynk server
    
}
