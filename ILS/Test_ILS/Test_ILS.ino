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


const int pin_ils = 8;
const int pin_led = 13; 

int etat_ils = 0;
int etat_ils_mem = 0;
int nb_ouverture = 0;


void setup() {

  //Initialisation 
  pinMode(pin_ils, INPUT);
  
  pinMode(pin_led, OUTPUT);
}

void loop() {
  // Création de l'instance Message de type PrintFr 
  PrintFr Message;  

  etat_ils = digitalRead(pin_ils);

  
  if (etat_ils != etat_ils_mem) {

    if (etat_ils == HIGH) {
          Message.Affiche("Ouverture porte");
          digitalWrite(pin_led, HIGH);
    } else {  
      digitalWrite(pin_led,LOW);
      Message.Affiche("Fermeture porte");
      nb_ouverture++;
      Message.Affiche("Nombre d'ouverture de porte : ",false);
      Serial.println(nb_ouverture);
    }
    //Tempo boucle
    delay(50);
  }
  //Enregistrement de l'état de l'ILS
  etat_ils_mem = etat_ils;
 
  

}
