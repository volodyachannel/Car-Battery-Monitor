// Скетч с созданием точки доступа
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "Carmon" // Имя создаваемой точки доступа
#define APPSK  "password" // Пароль для создаваемой точки доступа
#endif

const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

const int led = 13;
float b,k=20.0023657667,a; // k - рассчитывается исходя из коэффициента деления резисторного делителя (более подробно в видео)
uint16_t c=0;

void handleRoot() {
  c++;

  for(int i=0;i<100;i++){
  a+=analogRead(A0);
  }
  a/=100;
  b=(int)a*3.31/1023*k-0.3695; // 3.31 - Измеренное напряжение мультиметром на выходе 3.3В (В целом, можно оставить 3.3)
                               // 0.3695 - Число для устранения погрешности при измерении через АЦП ESP8266
  server.send(200, "text/plain"," Analog: "+String((int)a)+"\r\n Voltage: " + String(b) + "\r\n Updates count: " + String(c));
  a=0;
}

void setup(void) {
  delay(1000);
  pinMode(A0,INPUT);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.begin();
}

void loop(void) {
  server.handleClient();
}
