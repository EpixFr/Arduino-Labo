//-----------------------------------------------------------
//
//                Test module ILS pour Arduino
//           Interrupteur Lame Souple / Reed Switch
//  
//-----------------------------------------------------------
// EpixFR - Février 2017 
// Source matériel : http://www.ebay.fr/itm/182149404898
//-----------------------------------------------------------

// Inclusion de la bibliothèque pour les messages en Français
#include <PrintFr.h> //Source : https://github.com/EpixFr/Arduino-PrintFr

/* Déclaration des constantes définissant l'utilisation des broches */

//Broche utilisée pour les données du contact ILS
const int pin_ils = 8;
//Broche utilisée pour la Led (intégrée à la carte Arduino Uno)
const int pin_led = 13; 

/* Déclaration des variables globales */
//Etat du contact ILS
int etat_ils = 0;
//Etat précédent enregistré du contact ILS
int etat_ils_mem = 0;
//Nombre de cycle ouverture/fermeture
int nb_ouverture = 0;


void setup() {
  //Initialisation de la broche ILS en entrée numérique
  pinMode(pin_ils, INPUT);
  //Initialisation de la broche LED en sortie numérique
  pinMode(pin_led, OUTPUT);
}

void loop() {
  //Création de l'instance Message de type PrintFr 
  PrintFr Message;  

  //Ecoute du contact ILS
  etat_ils = digitalRead(pin_ils);

  //Si l'état ILS est différent de celui enregistré
  if (etat_ils != etat_ils_mem) {

    //Si le contact est ouvert (donc l'aimant est éloigné) 
    if (etat_ils == HIGH) {
          Message.Affiche("Ouverture porte");
          //On allume la LED de l'Arduino
          digitalWrite(pin_led, HIGH);
    } else {  
      //On éteint la LED de l'arduino
      digitalWrite(pin_led,LOW);
      Message.Affiche("Fermeture porte");
      //On incrémente le compteur d'ouverture
      nb_ouverture++;
      Message.Affiche("Nombre d'ouverture de porte : ",false);
      Serial.println(nb_ouverture);
    }
    //Petite temporisation pour la stabilité de l'acquisition des données
    delay(50);
  }
  //Enregistrement de l'état de l'ILS
  etat_ils_mem = etat_ils;
}
