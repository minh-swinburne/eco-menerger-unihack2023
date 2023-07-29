
//Thư viện: https://github.com/rkoptev/ACS712-arduino
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "ACS712.h"

ACS712 sensor1(ACS712_05B, A0); //Cảm biến 05B, kết nối chân A0
ACS712 sensor2(ACS712_05B, A5); //Cảm biến 05B, kết nối chân A5
//ACS712_05B
//ACS712_20A
//ACS712_30A
SoftwareSerial nodemcu(5, 6);

float tong1;
float I1;
float I_TB1;
float ma1;

float tong2;
float I2;
float I_TB2;
float ma2;

void setup() 
{
  Serial.begin(9600);
  nodemcu.begin(9600);

  // calibrate cảm biến
  // Trong quá trình cali phải đảm bảo KHÔNG có dòng điện đi qua cảm biến
  Serial.println("Đảm bảo không có dòng điện đi qua cảm biến trong quá trình cân bằng");
  delay(1000);
  Serial.println("Calibrating...");
  delay(200);
  sensor1.calibrate();
  sensor2.calibrate();
  Serial.println("Quá trình cân bằng hoàn tất!!!");
}

void loop() 
{
  for (int i=0; i<=100; i++)
  {
    I1 = sensor1.getCurrentAC(); //Đo dòng AC
    //Serial.print("I = "); Serial.print(I); Serial.print("   ");
    tong1 = tong1 + I1;
    //Serial.print("Tổng = "); Serial.println(tong);
  }
  I_TB1 = tong1/100;
  tong1 = 0;
  //Serial.print("\t\t\t");
  Serial.print("I1 = "); Serial.print(I_TB1); Serial.print("A"); Serial.print("   ");
  ma1 = I_TB1 * 1000;   
  Serial.print("mA1 = "); Serial.print(ma1); Serial.println("mA");
  delay(100);

  for (int i=0; i <= 100; i++)
  {
    I2 = sensor2.getCurrentAC(); //Đo dòng AC
    //Serial.print("I = "); Serial.print(I); Serial.print("   ");
    tong2 = tong2 + I2;
    //Serial.print("Tổng = "); Serial.println(tong);
  }
  I_TB2 = tong2/100;
  tong2 = 0;
  //Serial.print("\t\t\t");
  Serial.print("I2 = "); Serial.print(I_TB2); Serial.print("A"); Serial.print("   ");
  ma2 = I_TB2 * 1000;   
  Serial.print("mA2 = "); Serial.print(ma2); Serial.println("mA");
  delay(100);

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  //Assign collected data to JSON Object
  data["mA1"] = ma1;
  data["mA2"] = ma2; 

  //Send data to NodeMCU
  data.printTo(nodemcu);
  jsonBuffer.clear();

  delay(2000);
}
