/*
  NodeMCU-BlinkendeLED
  Led an dem Modul ESP8266 bzw. Board NodeMCU blinken lassen
  Programm erprobt ab Arduino IDE 1.6.13
  Weitere Beispiele unter http://www.mikrocontroller-elektronik.de/
*/

#include <ESP8266WiFi.h>

#define LED 2 //GPIO16 Interne Led auf dem NodeMCU Board 
//oft auch bereits als LED_BUILTIN definiert
//man koennte auch schreiben #define LED  16 (was das gleiche ist)

// #define LED D7 //nur Falls du externe LED z.B. an D7 (GPIO13)
// über ca. 330 Ohm Widerstand angeschlossen hast auskommentieren

const char* ssid = "Black Ice";
const char* password = "gast0815abc";

// Web Server on port 80
WiFiServer server(80);



void setup() {
  pinMode(LED, OUTPUT); // Port aus Ausgang schalten
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Verbinde mich mit Netz: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Verbindung aufgebaut");
  Serial.print("Eigene IP des ESP-Modul: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting web server");
  // Starting the web server
  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(10000);
  Serial.println("web server started");

}

void loop() {
  digitalWrite(LED, LOW); //Led port ausschalten
  delay(1000); //1 Sek Pause
  digitalWrite(LED, HIGH); //Led port einschlaten
  delay(1000);
}
