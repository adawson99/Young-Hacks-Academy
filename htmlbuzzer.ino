#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define ESP8266_SSID "MY_SSID"
//password must be at least 8 characters
#define ESP8266_PASSWORD "12345678"
#define buzzerPin D3

ESP8266WebServer server;

const char INDEX_HTML[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<title>ESP8266</title>"
  "<style>"
    "body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: Maroon; }"
  "</style>"
  "</head>"
  "<body>"
  "<h1>ESP8266 Standalone Access Point Demo</h1>"
  "<button onclick='toggle()'>Toggle LED</button>"
  "<button onclick='buzz()'>Buzz Buzzer</button>"
  "<script>"
    "function toggle(){"
      "fetch('/toggle').then(stream=>stream.text()).then(text=>console.log(text))"
    "}"
    "function buzz(){"
      "fetch('/buzz').then(stream=>stream.text()).then(text=>console.log(text))"
    "}"
  "</script>"
  "</body>"
  "</html>";

void setup()
{
  Serial.begin(9600);
  setupWiFi();
  
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN,LOW);
  pinMode(buzzerPin, OUTPUT); 

  server.on("/",sendIndex);
  server.on("/toggle", toggleLED);
  server.on("/buzz", buzzBuzzer);
  server.begin();
  Serial.println("");
  Serial.println("");
  Serial.print("Server running on http://192.168.4.1/");
}

void loop()
{
  server.handleClient();
}

void sendIndex(){
  server.send(200,"text/html",INDEX_HTML);  
}

void toggleLED(){
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  //server.send(204,"");
  server.send(200,"text/plain","Toggle!\n");
}

void buzzBuzzer(){
  //tone( pin number, frequency in hertz, duration in milliseconds);
  tone(buzzerPin,1300,500);
  delay(500);
  digitalWrite(buzzerPin,LOW);
  server.send(200,"text/plain","Buzz!\n");
}

void setupWiFi()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ESP8266_SSID, ESP8266_PASSWORD);
}
