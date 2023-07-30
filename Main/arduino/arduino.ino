//Sending Data from Arduino to NodeMCU Via Serial Communication
//NodeMCU code

//Include Lib for Arduino to Nodemcu
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ACS712.h>

//Initialise Arduino to NodeMCU (9=Rx & 10=Tx)
SoftwareSerial nodemcu(9,10);
//Initialise NodeMCU to Arduino (5=Rx & 6=Tx)
SoftwareSerial arduino(5,6);

#define INPUT1 A0
#define INPUT2 A5
#define SOC1 11
#define SOC2 12
#define BUT1 2
#define BUT2 3

ACS712 sensor1(ACS712_05B, INPUT1); //Cảm biến 05B, kết nối chân A0
ACS712 sensor2(ACS712_05B, INPUT2); //Cảm biến 05B, kết nối chân A5
//ACS712_05B
//ACS712_20A
//ACS712_30A

float tong1, I1, I_TB1, ma1;
float tong2, I2, I_TB2, ma2;
int record1 = 0, record2 = 0;
boolean state1 = 0, state2 = 0;

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  nodemcu.begin(9600);
  arduino.begin(9600);
  pinMode(SOC1, OUTPUT);
  pinMode(SOC2, OUTPUT);
  pinMode(BUT1, OUTPUT);
  pinMode(BUT2, OUTPUT);
  
  // calibrate cảm biến
  // Trong quá trình cali phải đảm bảo KHÔNG có dòng điện đi qua cảm biến
  Serial.println("Đảm bảo không có dòng điện đi qua cảm biến trong quá trình cân bằng");
  delay(1000);
  Serial.println("Calibrating...");
  delay(200);
  sensor1.calibrate();
  sensor2.calibrate();
  Serial.println("Quá trình cân bằng hoàn tất!!!");
  while (!Serial) continue;
}

void loop() {
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  // int tempa12 = digitalRead(12);
  // int tempa13 = digitalRead(13);
  // if(BUT2 == 1 && BUT1 == 0)
  // {
  //   change(10);
  // }
  // if(BUT1 == 1 && BUT2 == 0)
  // {
  //   change(11);
  // }
  // a12 = BUT1;
  // tempa13 = BUT2;

  acs712_func();

  data["mA1"] = ma1;
  data["mA2"] = ma2;
  
  data.printTo(nodemcu);
}

void from_nodemcu() {
  char json[] = "{\"arduino\":{}}";
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  if (root.containsKey("arduino")) {
    StaticJsonBuffer<500> jsonBuffer;
    JsonObject& data = jsonBuffer.parseObject(arduino);
    if (data == JsonObject::invalid()) {
    Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

    Serial.println("JSON Object Recieved");
    Serial.print("Recieved Socket 1 switch:  ");
    int switch1 = data["socket1"];
    Serial.println(switch1);
    if ((abs(record1 - switch1) % 2) != 0)  {
      change(SOC1);
      Serial.println("Switched Socket 1!");
    }
    Serial.print("Recieved Socket 2 switch:  ");
    int switch2 = data["socket2"];
    Serial.println(switch2);
    Serial.println("-----------------------------------------");
    if((abs(record2 - switch2) % 2) != 0)  {
      change(SOC2);
      Serial.println("Switched Socket 2!");
    }

    record1 = switch1;
    record2 = switch2;
  }
}

// void to_nodemcu() {


//   //Obtain Soil Moisture data
//   acs712_func();

//   //Assign collected data to JSON Object

//   data["socket1"] = digitalRead(SOC1);
//   data["socket2"] = digitalRead(SOC2); 

//   //Send data to NodeMCU
//   data.printTo(nodemcu);
//   Serial.println("Data sent to NodeMCU!");
//   jsonBuffer.clear();
// }

void switch_socket1()  {
   change(SOC1);
}
void switch_socket2()  {
   change(SOC2);
}

void change(int c)
{
  if(digitalRead(c) == LOW)
  {
    digitalWrite(c, HIGH);
  }
  else
  {
    digitalWrite(c, LOW);
  }
}

void acs712_func()  {
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
}

// void from_nodemcu() {
//   char json[] = "{\"arduino\":{}}";
//   StaticJsonBuffer<100> jsonBuffer;
//   JsonObject& root = jsonBuffer.parseObject(json);
//   if (root.containsKey("arduino")) {
//     StaticJsonBuffer<500> jsonBuffer;
//     JsonObject& data = jsonBuffer.parseObject(arduino);
//     if (data == JsonObject::invalid()) {
//     Serial.println("Invalid Json Object");
//     jsonBuffer.clear();
//     return;
//   }

//     Serial.println("JSON Object Recieved");
//     Serial.print("Recieved Socket 1 switch:  ");
//     int switch1 = data["socket1"];
//     Serial.println(switch1);
//     if ((abs(record1 - switch1) % 2) != 0)  {
//       change(SOC1);
//       Serial.println("Switched Socket 1!");
//     }
//     Serial.print("Recieved Socket 2 switch:  ");
//     int switch2 = data["socket2"];
//     Serial.println(switch2);
//     Serial.println("-----------------------------------------");
//     if((abs(record2 - switch2) % 2) != 0)  {
//       change(SOC2);
//       Serial.println("Switched Socket 2!");
//     }

//     record1 = switch1;
//     record2 = switch2;
//   }
// }

// void to_nodemcu() {
//   StaticJsonBuffer<500> jsonBuffer;
//   JsonObject& data = jsonBuffer.createObject();

//   //Obtain Soil Moisture data
//   acs712_func();

//   //Assign collected data to JSON Object
//   data["mA1"] = ma1;
//   data["mA2"] = ma2;
//   data["socket1"] = digitalRead(SOC1);
//   data["socket2"] = digitalRead(SOC2); 

//   //Send data to NodeMCU
//   data.printTo(nodemcu);
//   Serial.println("Data sent to NodeMCU!");
//   jsonBuffer.clear();
// }

// void switch_socket1()  {
//    change(SOC1);
// }
// void switch_socket2()  {
//    change(SOC2);
// }

// void acs712_func()  {
//   for (int i=0; i<=100; i++)
//   {
//     I1 = sensor1.getCurrentAC(); //Đo dòng AC
//     Serial.print("I = "); Serial.print(I1); Serial.print("   ");
//     tong1 = tong1 + I1;
//     Serial.print("Tổng = "); Serial.println(tong1);
//   }
//   I_TB1 = tong1/100;
//   tong1 = 0;
//   Serial.print("\t\t\t");
//   Serial.print("I1 = "); Serial.print(I_TB1); Serial.print("A"); Serial.print("   ");
//   ma1 = I_TB1 * 1000;   
//   Serial.print("mA1 = "); Serial.print(ma1); Serial.println("mA");

//   for (int i=0; i <= 100; i++)
//   {
//     I2 = sensor2.getCurrentAC(); //Đo dòng AC
//     Serial.print("I = "); Serial.print(I2); Serial.print("   ");
//     tong2 = tong2 + I2;
//     Serial.print("Tổng = "); Serial.println(tong2);
//   }
//   I_TB2 = tong2/100;
//   tong2 = 0;
//   Serial.print("\t\t\t");
//   Serial.print("I2 = "); Serial.print(I_TB2); Serial.print("A"); Serial.print("   ");
//   ma2 = I_TB2 * 1000;   
//   Serial.print("mA2 = "); Serial.print(ma2); Serial.println("mA");
// }

// void change(int c)
// {
//   if(digitalRead(c) == LOW)
//   {
//     digitalWrite(c, HIGH);
//   }
//   else
//   {
//     digitalWrite(c, LOW);
//   }
// }