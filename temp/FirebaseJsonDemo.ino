/*
  Make sure your Firebase project's ".read" and ".write" rules are set to "true".
  Avoiding this will result in an error.
  For more details- https://github.com/Rupakpoddar/ESP8266Firebase/blob/master/README.md
*/

#include <ArduinoJson.h>  // https://github.com/bblanchon/ArduinoJson
#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

#define _SSID "Zone 7 FPT"                   // Your WiFi SSID
#define _PASSWORD "777777777"              // Your WiFi Password
#define PROJECT_ID "lightning-demo-66e13"  // Your Firebase Project ID. Can be found in project settings.
#define FINGERPRINT "BA 24 75 4D AB 45 63 9E 01 8D 54 6F 2C D9 E9 30 20 EC DC FF"
#define HOST_REALTIME_DB "https://smartelectric-d9ea5-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define AUTH_KEY "oq9J9Q9wu8ae70MviHwO2xCLKoXyE0BhiFMg6WAw"

/*
  // FAST METHOD
  // REQUIRES PERIODIC UPDATE OF FINGERPRINT (EVERY 1 YEAR)
  // OUTDATED FINGERPRINT WILL STOP THE SERVICE
  // LATEST FINGERPRINT CAN BE FOUND AT- https://www.grc.com/fingerprints.htm?domain=test.firebaseio.com
  // REPLACE COLONS(:) WITH A SPACE(" ") AS SHOWN BELOW
  // 03:9E:4F:E6:83:FC:40:EF:FC:B2:C5:EF:36:0E:7C:3C:42:20:1B:8F ==> 03 9E 4F E6 83 FC 40 EF FC B2 C5 EF 36 0E 7C 3C 42 20 1B 8F
  #define FINGERPRINT "03 9E 4F E6 83 FC 40 EF FC B2 C5 EF 36 0E 7C 3C 42 20 1B 8F"
  Firebase firebase(PROJECT_ID, FINGERPRINT);
  // UNCOMMENT THIS BLOCK AND COMMENT THE LINE BELOW
*/

Firebase firebase(HOST_REALTIME_DB, FINGERPRINT, AUTH_KEY);  // SLOW BUT HASTLE-FREE METHOD FOR LONG TERM USAGE. DOES NOT REQUIRE PERIODIC UPDATE OF FINGERPRINT
//Firebase::Firebase(const char* HOST_REALTIME_DB, const char* FIREBASE_FINGERPRINT, const char* AUTH_KEY){
void setup() {
  Serial.begin(115200);
  firebase.json(true);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);
  //================================================================//
}

void loop() {
  
  //================================================================//

  // Write some data to the realtime database.
  Serial.println("-----setString-----");
  Serial.println(firebase.setString("Example/setString", "It's Working"));
  Serial.println("-----setInt-----");
  Serial.println(firebase.setInt("Example/setInt", 123));
  Serial.println("-----setFloat-----");
  Serial.println(firebase.setFloat("Example/setFloat", 45.32));

  String data = firebase.getString("Example");  // Get data from the database.

  // Deserialize the data.
  // Consider using Arduino Json Assistant- https://arduinojson.org/v6/assistant/
  const size_t capacity = JSON_OBJECT_SIZE(3) + 50;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, data);

  // Store the deserialized data.
  const char* received_String = doc["setString"];  // "It's Working"
  int received_int = doc["setInt"];                // 123
  float received_float = doc["setFloat"];          // 45.32

  // Print data
  Serial.print("Received String: ");
  Serial.println(received_String);

  Serial.print("Received int: ");
  Serial.println(received_int);

  Serial.print("Received float: ");
  Serial.println(received_float);

  // Delete data from the realtime database.
  // firebase.deleteData("Example");
  delay(3000);
}
