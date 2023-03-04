//Скетч для подключения к созданной точке доступа
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "kotiko" // Имя сети Wifi к которой будет подключение
#define STAPSK  "kitkotel1" // Пароль
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = 13;
float a,k=20.0023657667; // k - рассчитывается исходя из коэффициента деления резисторного делителя (более подробно в видео)
uint16_t c=0;

void handleRoot() {
  c++;
  digitalWrite(led, 1);
  a=analogRead(A0)*3.3/1023*k-0.3695; // 3.31 - Измеренное напряжение мультиметром на выходе 3.3В (В целом, можно оставить 3.3)
                                      // 0.3695 - Число для устранения погрешности при измерении через АЦП ESP8266
  server.send(200, "text/plain"," Voltage: " + String(a) + "\r\n Updates count: " + String(c));
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  pinMode(A0,INPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("carmon")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
