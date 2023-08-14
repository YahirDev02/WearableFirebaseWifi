//Librerias de firebase y placa wifi
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
//Librerias para la pantalla oled.
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define OLED_Address 0x3C
Adafruit_SSD1306 oled(1);
//#include "DHT.h"
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
/*-------------------------Saludo------------------------------*/
void saludo(){
  oled.clearDisplay();
  oled.display();
  
  oled.setTextSize(1);    
  oled.setCursor(40,0);
  oled.setTextColor(WHITE);
  oled.println("CAREBEAT"); 
  oled.setTextSize(2);    
  oled.setCursor(5,8);
  oled.setTextColor(WHITE,BLACK);
  oled.println("Ing. 9no A"); 
  oled.setTextSize(1);  
  oled.setTextColor(WHITE);
  //oled.println("ABCDEFGHIJKLMNOPQRSTU");       Guía para el rango del ancho de las letras
  oled.println("    PROYECTO FINAL   ");
  oled.display();//Finally display the created image
}
/*---------------------------------------------------------------*/
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


  /*Serial.println(F("DHT test"));
  dht.begin();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falla de lectura del sensor"));
    return;
  }+/
  /*-------------------------Saludo----------------------------*/
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.display();
  saludo();
  delay(4000);
  oled.clearDisplay();
  oled.display();
}

void loop() {
  delay(2500);
  /*h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.println(", Temperatura: ");
  Serial.println(t);
  Serial.println("");*/
  
  t = Firebase.getInt("sensor/temperatura");

  Serial.println(", Temperatura: ");
  Serial.println(t);

  if (t == 30) {
    statusClima = "Temperatura estable";
    oled.clearDisplay();
    oled.display();
    Firebase.setString("estado/status",statusClima);
  }else if(t < 30) {
    statusClima = "Temperatura baja";
    oled.clearDisplay();
    oled.display();
    Firebase.setString("estado/status",statusClima );
  }else if (t >= 31){
    statusClima = "Temperatura alta";
    oled.clearDisplay();
    oled.display();
    Firebase.setString("estado/status",statusClima );
  } else {
    oled.clearDisplay();
    oled.display();
    Firebase.setString("estado/status",statusInfo );
  }

  /*------------pantalla oled-----------*/
  oled.setTextSize(1);    
  oled.setCursor(40,0);
  oled.setTextColor(WHITE);
  oled.println("CAREBEAT");  
  oled.setTextSize(2);    
  oled.setCursor(55,8);
  oled.setTextColor(WHITE);
  oled.println(t);
  oled.setTextSize(1);  
  oled.setTextColor(WHITE);
  //oled.println("ABCDEFGHIJKLMNOPQRSTU");       Guía para el rango del ancho de las letras
   oled.println(statusClima);
  oled.display();//Finally display the created image
  
  if (Firebase.failed()) {
      Serial.print("Getting/Value failed");
      Serial.println(Firebase.error()); 
      delay(600); 
      return;
  }
}
