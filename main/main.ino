// Librairie Custom
#include <Parametre.h>
#include <EcranLCD.h>

// KeyPad Librairie
#include "SoftwareSerial.h"

#if defined(ARDUINO_ARCH_AVR)
SoftwareSerial mySerial(A0,A1);
#define KeyPad mySerial
#elif defined(ARDUINO_ARCH_SAMD)
#define KeyPad Serial
#else

#endif

// Ecran LCD 
#include <Wire.h>
#include "rgb_lcd.h"

CommandeLCD myLCD; // Mon écran
Parametre Par; // Initialiser la librairie

// Compteurs
long currentMillis = 0; // L'horloge de l'arduino

// Variables pour la vérification de la demande faites par l'utilisateur
long countUser = 10; // Valeur const 
long timerUser = 0; // Timer 
bool demandeStart  = currentMillis - timerUser >= countUser; // Savoir si l'utilisateur peut faire une demande

// Variables pour la détection des capteurs quand le moteur s'active 
long timerStart = 0; // Timer
long countStart = 600;  // valeur const 
bool boolStart = currentMillis - timerStart > countStart; // Savoir si les capteurs sont détecté par le système 

long timerLed = 0; 
long const countTimerLedChange = 100; // Temps d'activation et de désactivation de la LED à 100ms
long const countTimerLedStop = 400; // temps d'activation et de désactivation de la LED à 400ms
long countTimerLed = 0; // Temps d'activation et de désactivation de la LED


// Conditions 
bool objetDetecte = false; // Detecter par le capteur 
bool fermetureEnCours = false; // En changement d'état 
bool ouvertureEnCours = false; // En changement d'état 
bool demande = false; // Detection de l'utilisateur 
bool moteurWork = false; // Moteur en marche 
bool capteurs; // Capteurs détecté 

bool capteurOuvert = false; // portail Ouvert 
bool capteurFerme = false; // Portail fermer 

bool demandeExtAccept = false; // Le MDP est correct et le bouton extérieur est activé

void setup() 
{
  // Pour l'affichage dans le moniteur série
  Serial.begin(9600);
  
  // Initialiser LCD
  myLCD.LCD();

  // Initialisation des différents composants
  CapteurInitialisation();

  CapteurVerification(); // Verifier les différents capteurs

  // fermer le portail au démarrage s'il ne l'est pas
  if(!capteurFerme)
  {
    MoteurStart(true);
    fermetureEnCours = true;
  }
  else // Afficher Fermer
    LCDFermer();
}

// The loop function runs over and over again forever 

void loop() {
  // Initialiser les millisecondes 
  currentMillis = millis();
  demandeExtAccept = MDPVerification(); // Vérifier si le mdp doit être taper et si le mot de passe est correct

  // Vérifier les différents capteurs 
  CapteurVerification();

  // Vérification de certaines conditions
  demandeStart = !Par.TimerBelow(timerUser, countUser, currentMillis); // Savoir si la demande peut être accepté (Si délais en dessous de la sécurité, ne rien faire)
  boolStart = !Par.TimerBelow(timerStart, countStart, currentMillis); // Savoir si le système détecte les capteurs
  capteurs = capteurOuvert || capteurFerme; // Initialisation de la variable pour le changement d'état  

  // Essaye d'arrêter le mouvement du portail 
  if(TryStopAction()) 
  {
    // Si le portail s'arrete d'un coups
    if(ouvertureEnCours || fermetureEnCours)
      LCDStop(); // Afficher Arret    
  }

  // Changer le sens ou démarrer le mouvement du portail
  
  // Avec le RasberryPi / Site web
  if(CheckRasberryPi())
  {
    // Mettre en marche le moteur
    MoteurStart(fermetureEnCours);
  }
  // Avec le bouton pressoir 
  if( (demande && demandeStart))
    PortailChange();
  
  // Sécurité si l'utilisateur reste appuyé sur le bouton
  else if(demande && !demandeStart)
    timerUser = currentMillis;

// Activation de la LED
  LEDActivation();
}

// Changer le sens ou démarrer le mouvement du portail
bool PortailChange()
{
  timerUser = currentMillis; // Initialiser le delay de demande

  // Met en marche le moteur dans la direction souhaité
  FermerOuOuvert();

  timerLed = currentMillis;
  return true;
}

// Fermer ou ouvrir le portail
bool FermerOuOuvert()
{
  if(capteurs) // Portail à l'arrêt : Faire marcher le moteur
  {
    timerStart = currentMillis; // Sécurité 
    ouvertureEnCours = capteurFerme;  // Si le portail est fermer, le portail va s'ouvrir
    fermetureEnCours = capteurOuvert; // Si le portail est ouvert, le portail se ferme
  }

  // Si le portail est en mouvement 
  else if (MoteurState())
  {
    ouvertureEnCours = !ouvertureEnCours; 
    fermetureEnCours = !fermetureEnCours;
  }
  // Mettre en marche le moteur
  MoteurStart(fermetureEnCours);

  return ouvertureEnCours;
}

bool TryStopAction()
{
  // Objet détecté et en cours de fermeture
  if(objetDetecte && fermetureEnCours && MoteurState())
  {
    // Arrêter moteur
    MoteurStop();
    return true;
  }
  
  // Fin de cycle du portail
  if (capteurs && boolStart) // Capteur détecte le portail
  {
    // Arrêter moteur
    if(MoteurState())
      MoteurStop();
    
    if(fermetureEnCours || ouvertureEnCours)
    {
      // Renitialiser valeurs
      fermetureEnCours = false;
      ouvertureEnCours = false;

      // Afficher texte pour l'état correspondant
      LCDDisplay();
    }

    return true;
  }

  return false;
}
