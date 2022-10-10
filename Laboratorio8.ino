#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include "config.h"

// Creamos el servidor AsyncWebServer en el puerto 80
AsyncWebServer server(80);

// Create an Event Source on /events
AsyncEventSource events("/events");

// Valores ajustados para el SG90
#define COUNT_LOW 1638
#define COUNT_HIGH 7864
#define TIMER_WIDTH 16
int i;
// Inicializando LittleFS
void initFS()
{
   // Iniciamos  SPIFFS
   if (!SPIFFS.begin())
   {
      Serial.println("ha ocurrido un error al montar SPIFFS");
      return;
   }
}

// Inicializando WiFi
void initWiFi()
{
   // conectamos al Wi-Fi
   WiFi.begin(ssid, password);
   // Mientras no se conecte, mantenemos un bucle con reintentos sucesivos
   while (WiFi.status() != WL_CONNECTED)
   {
      delay(1000);
      // Esperamos un segundo
      Serial.println("Conectando a la red WiFi..");
   }
   Serial.println();
   Serial.println(WiFi.SSID());
   Serial.print("Direccion IP:\t");
   // Imprimimos la ip que le ha dado nuestro router
   Serial.println(WiFi.localIP());
}

String processor(const String &var)
{
   Serial.print(var + " : ");
   if (var == "IP")
   {
      return String(WiFi.localIP().toString().c_str());
   }
   else if (var == "HOSTNAME")
   {
      return String(WiFi.getHostname());
   }
   else if (var == "STATUS")
   {
      return String(WiFi.status());
   }
   else if (var == "SSID")
   {
      return String(WiFi.SSID().c_str());
   }
   else if (var == "PSK")
   {
      return String(WiFi.psk().c_str());
   }
   else if (var == "BSSID")
   {
      return String(WiFi.BSSIDstr().c_str());
   }
   else if (var == "RSSI")
   {
      return String(WiFi.RSSI());
   }
}
// Los pines PWM GPIO recomendados en el ESP32 incluyen 2,4,12-19,21-23,25-27,32-33
void setup()
{
   Serial.begin(115200);
   ledcSetup(1, 50, TIMER_WIDTH); // canal 1, 50 Hz, 16-bit width
   ledcAttachPin(26, 1);          // GPIO 22 asignado al canal 1
   ledcSetup(2, 50, TIMER_WIDTH); // canal 2, 50 Hz, 16-bit width
   ledcAttachPin(25, 2);          // GPIO 19 asignado al canal 2
   initWiFi();
   initFS();
   // Ruta para cargar el archivo index.html
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send(SPIFFS, "/index.html", String(), false, processor); });

   server.serveStatic("/", SPIFFS, "/");

   // Ruta para poner el GPIO alto
   server.on("/RSSI", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send_P(200, "text/plain", getRSSI().c_str()); });

   events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);

  // Start server
  server.begin();
}

void loop()
{
   for (i = COUNT_LOW; i < COUNT_HIGH; i = i + 100)
   {
      ledcWrite(1, i); //  servo 1
      delay(20);
   }
   for (i = COUNT_HIGH; i > COUNT_LOW; i = i - 100)
   {
      ledcWrite(1, i); // servo 1
      delay(20);
   }
   for (i = COUNT_LOW; i < COUNT_HIGH; i = i + 100)
   {
      ledcWrite(2, i); //  servo 2
      delay(20);
   }
   for (i = COUNT_HIGH; i > COUNT_LOW; i = i - 100)
   {
      ledcWrite(2, i); //  servo 2
      delay(20);
   }
}
