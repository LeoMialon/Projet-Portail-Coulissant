// Librairie Custom
#include <Parametre.h>
#include <EcranLCD.h>
#include <ManageLED.h>
#include <Capteurs.h>

// KeyPad Librairie
#include "SoftwareSerial.h"

#if defined(ARDUINO_ARCH_AVR)
SoftwareSerial mySerial(A0, A1);
#define KeyPad mySerial
#elif defined(ARDUINO_ARCH_SAMD)
#define KeyPad Serial
#else

#endif

CommandeLCD myLCD;  // Mon écran
Parametre Par;      // Initialiser la librairie
GestionLED myLED;
Capteurs myCapteurs;

// Compteurs
long currentMillis = 0;  // L'horloge de l'arduino

// Variables pour la vérification de la demande faites par l'utilisateur
long countUser = 10;  // Valeur const
long timerUser = 0;   // Timer
bool demandeAccept;   // Savoir si l'utilisateur peut faire une demande

// Variables pour la détection des capteurs quand le moteur s'active
long timerStart = 0;    // Timer
long countStart = 600;  // valeur const
bool detectCapteur;     // Savoir si les capteurs sont détecté par le système

// Conditions
bool objetDetecte = false;      // Detecter par le capteur
bool fermetureEnCours = false;  // En changement d'état
bool ouvertureEnCours = false;  // En changement d'état
bool demande = false;           // Detection de l'utilisateur
bool moteurWork = false;        // Moteur en marche
bool capteurs;                  // Capteurs détecté

bool portailOuvert = false;  // portail Ouvert
bool portailFermer = false;  // Portail fermer

bool demandeExtAccept = false;  // Le MotDePasse est correct et le bouton extérieur est activé

void setup() {
  // Pour l'affichage dans le moniteur série
  Serial.begin(9600);
  // Pour le temps de lecture de la carte arduino sur le rasberry
  Serial.setTimeout(10);

  InitialisationLCD();

  InitialisationCapteurs();

  VerificationCapteurs();
  
  // fermer le portail au démarrage s'il ne l'est pas
  if (!portailFermer) {
    MoteurStart(true);
    fermetureEnCours = true;
  } else  // Afficher Fermer
    LCDFermer();
}

// The loop function runs over and over again forever

void loop() {
  // Initialiser les millisecondes
  currentMillis = millis();
  demandeExtAccept = MotDePasseVerification();  // Vérifier si le MotDePasse doit être taper et si le mot de passe est correct

  // Vérifier les différents capteurs
  VerificationCapteurs();

  // Vérification de certaines conditions
  demandeAccept = !Par.TimerBelow(timerUser, countUser, currentMillis) && detectCapteur;    // Savoir si la demande peut être accepté (Si délais en dessous de la sécurité, ne rien faire)
  detectCapteur = !Par.TimerBelow(timerStart, countStart, currentMillis);  // Savoir si le système détecte les capteurs
  capteurs = portailOuvert || portailFermer;                               // Initialisation de la variable pour le changement d'état

  // Essaye d'arrêter le mouvement du portail
  if (TryStopAction()) {
    // Si le portail s'arrete d'un coups
    if (ouvertureEnCours || fermetureEnCours)
      LCDStop();  // Afficher Arret
  }

  if(CheckRasberryPi())
  {
    PortailChange();
  }
  // Changer le sens ou démarrer le mouvement du portail
  // Avec le bouton pressoir
  if ((demande && demandeAccept))
    PortailChange();

  // Sécurité si l'utilisateur reste appuyé sur le bouton
  else if (demande && !demandeAccept)
    timerUser = currentMillis;

  // Activation de la LED
  myLED.ActiverLED(MoteurState(), capteurs, currentMillis);
}

// Changer le sens ou démarrer le mouvement du portail
bool PortailChange() {
  timerUser = currentMillis;  // Initialiser le delay de demande

  // Met en marche le moteur dans la direction souhaité
  FermerOuOuvrir();

  myLED.SetCompteurLED(currentMillis);
  return true;
}

// Fermer ou ouvrir le portail
bool FermerOuOuvrir() {
  if (capteurs) { // Portail à l'arrêt : Faire marcher le moteur
    timerStart = currentMillis;        // Sécurité
    ouvertureEnCours = portailFermer;  // Si le portail est fermer, le portail va s'ouvrir
    fermetureEnCours = portailOuvert;  // Si le portail est ouvert, le portail se ferme
  }

  // Si le portail est en mouvement
  else if (MoteurState()) {
    ouvertureEnCours = !ouvertureEnCours;
    fermetureEnCours = !fermetureEnCours;
  }
  // Mettre en marche le moteur
  MoteurStart(fermetureEnCours);

  return ouvertureEnCours;
}

bool TryStopAction() {
  // Objet détecté et en cours de fermeture
  if (objetDetecte && fermetureEnCours && MoteurState()) {
    // Arrêter moteur
    MoteurStop();
    return true;
  }

  // Fin de cycle du portail
  if (capteurs && detectCapteur) { // Capteur détecte le portail
    // Arrêter moteur
    if (MoteurState())
    {
      Par.Println((String)(currentMillis-timerStart));
      MoteurStop();
    }

    if (fermetureEnCours || ouvertureEnCours) {
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
