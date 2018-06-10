//-----------------------------------------------------------
//
//                Variateur de tension aléatoire
//   utilisé pour l'éclairage d'un guirlande led d'intérieur 
//
//-----------------------------------------------------------
// EpixFr - Juin 2018 
// Version : 1.1
//-----------------------------------------------------------

//Initialisation des variables
int ledPin = 11;     // La guirlande de LED est connectée à la broche 11
int randLuxMini = 0; // Initialisation de l'éclairage mini
int randLuxMax;      // Eclairage maxi
int LuxValue;        // Eclairage en cours
int randTempo;       // Tempo entre 2 changements d'éclairage
int randPas;         // Pas d'incrémentation

void setup() {
  // Initialisation de la séquence aléatoire
  randomSeed(analogRead(0));
  //Initialisation led à zéro
  analogWrite(ledPin, 0);   
}

void loop() {

  //Initialisation Tempo éclairage Max
  int randTempoPlus = random(5,20)*100;
  //Initialisation Tempo éclairage Mini
  int randTempoMoins = random(3,6)*100;

  /* ------------  Augmentation  ----------- */

  // Initialisation Eclairage max
  randLuxMax = random(180,255);
  // Initialisation pas d'incrémentation
  randPas = random(1,3);
  
  // Boucle augmentation de l'éclairage du mini au maxi 
  for (LuxValue = randLuxMini ; LuxValue <= randLuxMax; LuxValue += randPas) {
     analogWrite(ledPin, LuxValue);
    //Attente entre chaque changement pris aléatoirement
    randTempo = random(2,10)*5;
    delay(randTempo);
  }
  // Tempo éclairage max
  delay(randTempoPlus);

  /* ------------  Diminution  ----------- */

  // Initialisation Eclairage mini
  randLuxMini = random(0,15);
  // Initialisation pas d'incrémentation
  randPas = random(1,3);

  // Boucle diminution de l'éclairage du maxi au mini 
  for (LuxValue = randLuxMax ; LuxValue >= randLuxMini; LuxValue -= randPas) {
    analogWrite(ledPin, LuxValue);
    //Attente entre chaque changement pris aléatoirement
    randTempo = random(2,10)*5;
    delay(randTempo);
  }
  // Tempo éclairage mini
  delay(randTempoMoins);
}
