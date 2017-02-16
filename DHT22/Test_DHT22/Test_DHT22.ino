//--------------------------------------------
//
//        Test complet du capteur DHT22
//  
//-------------------------------------------
// EpixFR - Février 2017
// Attention fonctionnement en 3.3V
//-------------------------------------------
 
// Inclusion des bibliothèques pour le capteur DHT22
#include <Adafruit_Sensor.h> //Source : https://github.com/adafruit/Adafruit_Sensor
#include <DHT_U.h> //Source : https://github.com/adafruit/DHT-sensor-library

// Inclusion de la bibliothèque pour les messages en Français
#include <PrintFr.h> //Source : https://github.com/EpixFr/Arduino-PrintFr

// Définition du type de capteur
// Déclaration de l'input utilisé sur la carte Arduino
#define DHTPIN 2
// Déclaration du type de capteur DHTxx
#define DHTTYPE DHT22

// Création de l'objet de capteur DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

//Variable du délai de capture
float DelaiCapture;

void setup() {
  // Création de l'instance Message de type PrintFr 
  PrintFr Message;
  // Initialisation du capteur DHT22
  dht.begin();
  //Initialisation de la capture
  sensor_t sensor;
  //Capture des caractéristiques du capteur de température
  dht.temperature().getSensor(&sensor);
  Message.Affiche("*******************************************");
  Message.Ecrit("      Définition du capteur ",false); Message.Ecrit(sensor.name);
  Message.Affiche("*******************************************");
  Message.Affiche("-----------------------------");
  Message.Affiche(" Capteur de température");
  Message.Affiche("-----------------------------");
  Message.Affiche("   Valeur Mini :  ",false); Serial.print(sensor.min_value,1); Message.Affiche("°C");
  Message.Affiche("   Valeur Maxi :  ",false); Serial.print(sensor.max_value,1); Message.Affiche("°C");  
  Message.Affiche("   Résolution  :  ",false); Serial.print(sensor.resolution,2); Message.Affiche("°C");
  //Capture des caractéristiques du capteur d'humidité
  dht.humidity().getSensor(&sensor);
  Message.Affiche("-----------------------------");
  Message.Affiche(" Capteur d'humidité");
  Message.Affiche("-----------------------------");
  Message.Affiche("   Valeur Mini :  ",false); Serial.print(sensor.min_value,1); Message.Affiche("%");
  Message.Affiche("   Valeur Maxi :  ",false); Serial.print(sensor.max_value,1); Message.Affiche("%");  
  Message.Affiche("   Résolution  :  ",false); Serial.print(sensor.resolution,2); Message.Affiche("%");
  Message.Affiche("-----------------------------");
  //Calcul du délai mini entre 2 captures
  DelaiCapture = sensor.min_delay / 1000;
  Message.Affiche(" Délai mini entre 2 captures");
  Message.Affiche("-----------------------------");
  Message.Affiche("   ",false);Serial.print(DelaiCapture); Message.Affiche(" ms");
  Message.Affiche("-----------------------------");
  Message.Affiche("*******************************************");
  Message.Affiche("           Capture des données");
  Message.Affiche("*******************************************");
}

void loop() {
  // Création de l'instance Message de type PrintFr 
  PrintFr Message;  
  //Capture des données du capteur de température
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  //Si on n'a pas d'évènement on affiche un message d'erreur
  //sinon on affiche la température
  if (isnan(event.temperature)) {
    Message.Affiche("Lecture de la température impossible !");
  }
  else {
    Message.Affiche(" Température : ",false);
    Serial.print(event.temperature);
    Message.Affiche("°C", false);
    //Affichage séparateur
    Message.Affiche(" - ",false);  
  }
  
  //Capture des données du capteur d'humidité
  dht.humidity().getEvent(&event);
  //Si on n'a pas d'évènement on affiche un message d'erreur
  //sinon on affiche la température
  if (isnan(event.relative_humidity)) {
    Message.Affiche("Lecture de l'humidité impossible !");
  }
  else {
    Message.Affiche("Humidité : ",false);
    Serial.print(event.relative_humidity);
    Message.Affiche("%");
  }
  //Temporisation entre 2 captures (temps calculé dans le setup)
  delay(DelaiCapture);
}
