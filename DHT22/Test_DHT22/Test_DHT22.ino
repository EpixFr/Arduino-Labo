// Inclusion des bibliothèques pour le capteur DHT22
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
// Inclusion de la bibliothèque pour les messages en Français
#include <PrintFr.h>

// Définition du type de capteur
#define DHTPIN 2
#define DHTTYPE DHT22

// Création de l'objet de capteur DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

//Variable du délai de capture
float DelaiCapture;

void setup() {
  /* Création de l'instance Message de type PrintFr */
  PrintFr Message;
  // Initialisation du capteur DHT22
  dht.begin();
  sensor_t sensor;
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
  dht.humidity().getSensor(&sensor);
  Message.Affiche("-----------------------------");
  Message.Affiche(" Capteur d'humidité");
  Message.Affiche("-----------------------------");
  Message.Affiche("   Valeur Mini :  ",false); Serial.print(sensor.min_value,1); Message.Affiche("%");
  Message.Affiche("   Valeur Maxi :  ",false); Serial.print(sensor.max_value,1); Message.Affiche("%");  
  Message.Affiche("   Résolution  :  ",false); Serial.print(sensor.resolution,2); Message.Affiche("%");
  Message.Affiche("-----------------------------");
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
  /* Création de l'instance Message de type PrintFr */
  PrintFr Message;
  
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Message.Affiche("Lecture de la température impossible !");
  }
  else {
    Message.Affiche(" Température : ",false);
    Serial.print(event.temperature);
    Message.Affiche("°C", false);
  }

  Message.Affiche(" - ",false);
  
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Lecture de l'humidité impossible !");
  }
  else {
    Message.Affiche("Humidité : ",false);
    Serial.print(event.relative_humidity);
    Message.Affiche("%");
  }
  
  // Delay between measurements.
  delay(DelaiCapture);
}
