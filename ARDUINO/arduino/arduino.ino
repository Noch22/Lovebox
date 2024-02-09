#include <WiFiManager.h>
#include <Servo.h>
#include <Wire.h>
#include <ESP8266HTTPClient.h>
#include <BearSSLHelpers.h>
#include <ArduinoJson.h>
#include "Ecran.h"
Ecran display;
#define motorPin 16
int photo = A0;
Servo servo;
int pos = 90;
int position = 0;
int increment = -1;
String lastid;
String lastmsg;
const char* text;

unsigned long previousFiveMinutes = 0;  // Stocke le temps du dernier déclenchement de la fonction toutes les 5 minutes
const long fiveMinutesInterval = 300000;  // Intervalle de 5 minutes en millisecondes (300,000 ms)
// const long fiveMinutesInterval = 5000;  //intervale de 5 secondes pour le debug

void setup() {
  WiFi.mode(WIFI_STA);  // explicitly set mode, esp defaults to STA+AP
  WiFiManager wm;
  bool res;
  // *********************************
  // **                             **
  // **     Port servo moteur       **
  // **                             **
  // *********************************

  servo.attach(motorPin);

  // *********************************
  // **                             **
  // **     Clear,test screen       **
  // **                             **
  // *********************************

  const char* points[] = { ".", "..", "...", "...." };

  display.begin();
  display.effacer();
  // display.setCursor(0, 0);
  display.ecrire("LoveBox de prénom", 0, 1);
  display.refresh();
  for (const char* element : points) {
    // display.setCursor(0, 20);
    display.ecrire(element, 1, 1);
    display.refresh();
    delay(500);
  }
  delay(1000);
  display.effacer();
  display.refresh();
  display.ecrire("Connexion au wifi :", 0, 1);
  display.refresh();
  delay(5000);
  display.effacer();
  display.refresh();
  // *********************************
  // **                             **
  // **     Connexion au wifi       **
  // **                             **
  // *********************************

  Serial.begin(115200);
  // Se connecter au réseau Wi-Fi
  res = wm.autoConnect("Lovebox");  // password protected ap
  if (WiFi.status() != WL_CONNECTED) {
    while (WiFi.status() != WL_CONNECTED){
    Serial.println("Failed to connect");
    display.ecrire("Mauvais paramétrage du Wifi", 0, 1);
    display.refresh();
    }
  } else {
    //if you get here you have connected to the WiFi
    display.effacer();
    display.ecrire("Connecté au wifi !", 0, 1);
    display.refresh();
    Serial.println("Connecté au WiFi!");
    delay(2000);
  }

  pinMode(photo, INPUT);
  makeHttpRequest();
}

void loop() {
  unsigned long currentMillis = millis();
  display.refresh();

  int lecture = analogRead(photo);
  Serial.print("Lecture analogique : ");
  Serial.println(lecture);
  if (lecture <= 50) {
    EteindreEcran();
  } else {
    Ecran(lastmsg);
  }



  // *********************************
  // **                             **
  // **     Fonction toutes         **
  // **     les 5 minutes           **
  // *********************************

  if (currentMillis - previousFiveMinutes >= fiveMinutesInterval) {
    previousFiveMinutes = currentMillis;  // Mettre à jour le temps du dernier déclenchement
    makeHttpRequest();
  }
}


// *********************************
// **                             **
// **     Fonction qui fais       **
// **          la requete         **
// *********************************

void makeHttpRequest() {
  HTTPClient http;
  BearSSL::WiFiClientSecure client;

  // Adresse URL de la requête
  String url = "https://le_lien_pour_recupérer_le_dernier_message";

  // Commencer la connexion HTTP
  client.setInsecure();  // Désactiver la vérification du certificat SSL (pour le débogage uniquement)
  http.begin(client, url);

  // Envoyer la requête et attendre la réponse
  int httpCode = http.GET();

  // Vérifier le code de réponse
  if (httpCode > 0) {
    // La requête a réussi
    Serial.printf("[HTTP] Code de réponse: %d\n", httpCode);

    // Lire la réponse
    String payload = http.getString();
    Serial.println("Contenu de la réponse:");
    Serial.println(payload);

    StaticJsonDocument<200> doc;

    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    JsonObject obj = doc[0];
    const char* message = obj["message"];  // "test"
    const char* id_msg = obj["_id"];
    // Ecran(message);
    // Serial.println("Id : ");
    // Serial.print(id_msg);
    lastmsg = message;
    check(id_msg, message);
  } else {
    // La requête a échoué
    Serial.printf("[HTTP] La requête a échoué, code d'erreur: %s\n", http.errorToString(httpCode).c_str());
  }

  // Fermer la connexion HTTP
  http.end();
}

// *********************************
// **                             **
// **     Fonction ecrire         **
// **      ecran oled             **
// *********************************

void Ecran(String textEcran) {
  display.effacer();
  display.ecrire(textEcran, 0, 2);
}

void EteindreEcran() {
  display.effacer();
}

// *********************************
// **                             **
// **     Fonction servomot       **
// **                             **
// *********************************

void spinServo() {
  servo.write(pos);
  delay(50);  // wait 50ms to turn servo

  if (pos == 0 || pos == 180) {  // 75°-105° range
    increment *= -1;
  }
  pos += increment;
}


void check(String chid_msg, String chmessage) {
  int lecture = analogRead(photo);
  if (lastid == chid_msg) {
    Serial.println("meme id");
    Serial.println("last id : ");
    Serial.println(lastid);

  } else {
    delay(1000);
    Serial.print("i : ");
    Serial.print(lastid);
    Serial.print("chid_msg : ");
    Serial.print(chid_msg);
    Serial.print("chmessage : ");
    Serial.print(chmessage);
    while (lecture <= 50) {
      spinServo();
      EteindreEcran();
      lecture = analogRead(photo);
      Serial.print("Le servo tourne !");
    }
    servo.write(90);
    EteindreEcran();
    Ecran(chmessage);
    delay(1000);
    lastid = chid_msg;
    Serial.print("i modifié: ");
    Serial.print(lastid);
  }
}
