//Librerias de firebase y placa wifi
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
/*-------------------------FIREBASE------------------------------*/
//#define FIREBASE_HOST "esp8266-d4437-default-rtdb.firebaseio.com"
//#define FIREBASE_AUTH "QggQfB9P8ZPtuyfEIeGV2Uw2uwycNJvsviRulU8P"
#define FIREBASE_HOST "carebeat-d6096-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "JkyuweWeL408Oj0Ls6vr5lmNIhFYhFdyTFUrDZm3"
/*-------------------------Red Wifi------------------------------*/
//#define WIFI_SSID "PersonalUTT_Biblioteca"
//#define WIFI_PASS "biblio2016"
//#define WIFI_SSID "PersonalUTT_Edif3"
//#define WIFI_PASS "DocenteUTT2021"
#define WIFI_SSID "INFINITUM1A4D_2.4"
#define WIFI_PASS "nxMD4yU2QF"
/*---------------------------------------------------------------*/
#define DHTPIN 0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

byte h = 0; 
byte t = 0;

String statusClima = "";
String statusInfo = "Dato no disponible";
String grados = "°";

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  delay(2000);

  Serial.println("Conectando a la red wifi");
  Serial.println(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


  Serial.println(F("DHT test"));
  dht.begin();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falla de lectura del sensor"));
    return;
  }
}

void loop() {
  delay(2500);
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.println(", Temperatura: ");
  Serial.println(t);
  Serial.println("");

  Firebase.setInt("sensor/temperatura", t);

  if (t == 30) {
    statusClima = "Temperatura estable";
    Firebase.setString("estado/estatus",statusClima);
  }else if(t < 30) {
    statusClima = "Temperatura baja";
    Firebase.setString("estado/estatus",statusClima );
  }else if (t >= 31){
    statusClima = "Temperatura alta";
    Firebase.setString("estado/estatus",statusClima );
  } else {
    Firebase.setString("estado/estatus",statusInfo );
  }

  if (Firebase.failed()) {
      Serial.print("ERROR");
      Serial.println(Firebase.error());  
  }

}
