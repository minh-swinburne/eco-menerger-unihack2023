#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer webServer(80);
char const* ssid = "He";
char const* pass = "123456789";
//=========Biến chứa mã HTLM Website==//
const char MainPage[] PROGMEM = R"=====(
  <!DOCTYPE html> 
  <html>
   <head> 
       <title>HOME PAGE</title> 
       <style> 
          body {text-align:center;}
          h1 {color:#003399;}
          a {text-decoration: none;color:#FFFFFF;}
          .bt_on {height:50px; width:100px; margin:10px 0;background-color:#FF6600;border-radius:5px;}
          .bt_off {height:50px; width:100px; margin:10px 0;background-color:#00FF00;border-radius:5px;}
       </style>
       <meta charset="UTF-8">
   </head>
   <body> 
      <h1>ESP8266 Web Server</h1> 
      <div>Trạng thái trên chân D1: <b><pan id="trangthaiD1"><pan></b></div>
      <div>
        <button class="bt_on" onclick="getdata('onD1')">ON</button>
        <button class="bt_off" onclick="getdata('offD1')">OFF</button>
      </div>
      <div>Trạng thái trên chân D2: <b><pan id="trangthaiD2"><pan></b></div>
      <div>
        <button class="bt_on" onclick="getdata('onD2')">ON</button>
        <button class="bt_off" onclick="getdata('offD2')">OFF</button>
      </div>
      <div>Trạng thái trên chân D3: <b><pan id="trangthaiD3"><pan></b></div>
      <div>
        <button class="bt_on" onclick="getdata('onD3')">ON</button>
        <button class="bt_off" onclick="getdata('offD3')">OFF</button>
      </div>
      <div>Trạng thái trên chân D4: <b><pan id="trangthaiD4"><pan></b></div>
      <div>
        <button class="bt_on" onclick="getdata('onD4')">ON</button>
        <button class="bt_off" onclick="getdata('offD4')">OFF</button>
      </div>
      <div>Trạng thái trên chân D5: <b><pan id="trangthaiD5"><pan></b></div>
      <div>
        <button class="bt_on" onclick="getdata('onD5')">ON</button>
        <button class="bt_off" onclick="getdata('offD5')">OFF</button>
      </div>
      <div>Trạng thái trên chân D6: <b><pan id="trangthaiD6"><pan></b></div>
      <div>
        <button class="bt_on" onclick="getdata('onD6')">ON</button>
        <button class="bt_off" onclick="getdata('offD6')">OFF</button>
      </div>
      <div>Trạng thái trên chân D7: <b><pan id="trangthaiD7"><pan></b></div>
      <div>
        <button class="bt_on" onclick="getdata('onD7')">ON</button>
        <button class="bt_off" onclick="getdata('offD7')">OFF</button>
      </div>
      <div>Trạng thái trên chân D8: <b><pan id="trangthaiD8"><pan></b></div>
      <div>
        <button class="bt_on" onclick="getdata('onD8')">ON</button>
        <button class="bt_off" onclick="getdata('offD8')">OFF</button>
      </div>
      <div id="reponsetext"></div>
      <script>
        //-----------Tạo đối tượng request----------------
        function create_obj(){
          td = navigator.appName;
          if(td == "Microsoft Internet Explorer"){
            obj = new ActiveXObject("Microsoft.XMLHTTP");
          }else{
            obj = new XMLHttpRequest();
          }
          return obj;
        }
        var xhttp = create_obj();
        //-----------Thiết lập dữ liệu và gửi request-------
        function getdata(url){
          xhttp.open("GET","/"+url,true);
          xhttp.onreadystatechange = process;//nhận reponse 
          xhttp.send();
        }
        //-----------Kiểm tra response--------------------
        function process(){
          if(xhttp.readyState == 4 && xhttp.status == 200){
            //------Updat data sử dụng javascript----------
            ketqua = xhttp.responseText; 
            document.getElementById("reponsetext").innerHTML=ketqua;       
          }
        }
        //------------Kiểm tra trạng thái chân D1 D2------
        function getstatusD1D2(){
          xhttp.open("GET","getstatusD1D2",true);
          xhttp.onreadystatechange = process_json;
          xhttp.send();
        }
        //-----------Kiểm tra response-------------------------------
        function process_json(){
          if(xhttp.readyState == 4 && xhttp.status == 200){
            //------Update data sử dụng javascript-------------------
            var trangthaiD1D2_JSON = xhttp.responseText;
            var Obj = JSON.parse(trangthaiD1D2_JSON);
            document.getElementById("trangthaiD1").innerHTML = Obj.D1;
            document.getElementById("trangthaiD2").innerHTML = Obj.D2;
            document.getElementById("trangthaiD3").innerHTML = Obj.D3;
            document.getElementById("trangthaiD4").innerHTML = Obj.D4;
            document.getElementById("trangthaiD5").innerHTML = Obj.D5;
            document.getElementById("trangthaiD6").innerHTML = Obj.D6;
            document.getElementById("trangthaiD7").innerHTML = Obj.D7;
            document.getElementById("trangthaiD8").innerHTML = Obj.D8;
          }
        }
        //---Ham update duu lieu tu dong---
        setInterval(function() {
          getstatusD1D2();
        }, 1000);
      </script>
   </body> 
  </html>
)=====";
//=========================================//
void setup() {
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
  WiFi.begin(ssid,pass);
  Serial.begin(9600);
  Serial.print("Connecting");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print("...");
  }
  Serial.println(WiFi.localIP());

  webServer.on("/",mainpage);
  webServer.on("/onD1",on_D1);
  webServer.on("/offD1",off_D1);
  webServer.on("/onD2",on_D2);
  webServer.on("/offD2",off_D2);
  webServer.on("/onD3",on_D3);
  webServer.on("/offD3",off_D3);
  webServer.on("/onD4",on_D4);
  webServer.on("/offD4",off_D4);
  webServer.on("/onD5",on_D5);
  webServer.on("/offD5",off_D5);
  webServer.on("/onD6",on_D6);
  webServer.on("/offD6",off_D6);
  webServer.on("/onD7",on_D7);
  webServer.on("/offD7",off_D7);
  webServer.on("/onD8",on_D8);
  webServer.on("/offD8",off_D8);
  webServer.on("/getstatusD1D2",get_statusD1D2);
  webServer.begin();
}

void loop() {
  webServer.handleClient();
}
//==========Chương trình con=================//
void mainpage(){
  String s = FPSTR(MainPage);
  webServer.send(200,"text/html",s);
}
void on_D1(){
  digitalWrite(D1,HIGH);
  webServer.send(200,"text/html","CHÂN D1 ĐÃ ON");
}
void off_D1(){
  digitalWrite(D1,LOW);
  webServer.send(200,"text/html","CHÂN D1 ĐÃ OFF");
}
void on_D2(){
  digitalWrite(D2,HIGH);
  webServer.send(200,"text/html","CHÂN D2 ĐÃ ON");
}
void off_D2(){
  digitalWrite(D2,LOW);
  webServer.send(200,"text/html","CHÂN D2 ĐÃ OFF");
}
void on_D3(){
  digitalWrite(D3,HIGH);
  webServer.send(200,"text/html","CHÂN D3 ĐÃ ON");
}
void off_D3(){
  digitalWrite(D3,LOW);
  webServer.send(200,"text/html","CHÂN D3 ĐÃ OFF");
}
void on_D4(){
  digitalWrite(D4,HIGH);
  webServer.send(200,"text/html","CHÂN D4 ĐÃ ON");
}
void off_D4(){
  digitalWrite(D4,LOW);
  webServer.send(200,"text/html","CHÂN D4 ĐÃ OFF");
}void on_D5(){
  digitalWrite(D5,HIGH);
  webServer.send(200,"text/html","CHÂN D5 ĐÃ ON");
}
void off_D5(){
  digitalWrite(D5,LOW);
  webServer.send(200,"text/html","CHÂN D5 ĐÃ OFF");
}void on_D6(){
  digitalWrite(D6,HIGH);
  webServer.send(200,"text/html","CHÂN D6 ĐÃ ON");
}
void off_D6(){
  digitalWrite(D6,LOW);
  webServer.send(200,"text/html","CHÂN D6 ĐÃ OFF");
}void on_D7(){
  digitalWrite(D7,HIGH);
  webServer.send(200,"text/html","CHÂN D7 ĐÃ ON");
}
void off_D7(){
  digitalWrite(D7,LOW);
  webServer.send(200,"text/html","CHÂN D7 ĐÃ OFF");
}void on_D8(){
  digitalWrite(D8,HIGH);
  webServer.send(200,"text/html","CHÂN D8 ĐÃ ON");
}
void off_D8(){
  digitalWrite(D8,LOW);
  webServer.send(200,"text/html","CHÂN D8 ĐÃ OFF");
}
void get_statusD1D2(){
  String d1,d2, d3, d4, d5, d6, d7, d8;
  if(digitalRead(D1)==1){
    d1 = "ON";
  }else{
    d1 = "OFF";
  }
  if(digitalRead(D2)==1){
    d2 = "ON";
  }else{
    d2 = "OFF";
  }
  if(digitalRead(D3)==1){
    d3 = "ON";
  }else{
    d3 = "OFF";
  }
  if(digitalRead(D4)==1){
    d4 = "ON";
  }else{
    d4 = "OFF"; 
  }
  if(digitalRead(D5)==1){
    d5 = "ON";
  }else{
    d5 = "OFF";
  }
  if(digitalRead(D6)==1){
    d6 = "ON";
  }else{
    d6 = "OFF";
  }
  if(digitalRead(D7)==1){
    d7 = "ON";
  }else{
    d7 = "OFF";
  }
  if(digitalRead(D8)==1){
    d8 = "ON";
  }else{
    d8 = "OFF";
  }
  String s = "{\"D1\": \""+ d1 +"\",\"D2\": \""+ d2 +"\",\"D3\": \""+ d3 +"\",\"D4\": \""+ d4 +"\",\"D5\": \""+ d5 +"\",\"D6\": \""+ d6 +
  "\",\"D7\": \""+ d7 +"\",\"D8\": \""+ d8 +"\"}";
  webServer.send(200,"application/json",s);
}