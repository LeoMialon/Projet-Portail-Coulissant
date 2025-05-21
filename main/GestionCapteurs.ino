// Led
short ledPortail = 4;  // Activation de la led

// Capteurs FDC
short captOuvert = 5;  // Capteur Ouverture
short captFerme = A2;  // Capteur Fermeture

// Bouton Poussoirs
short bPInt = 2;  // Demande de l'utilisateur à l'intérieur
short bPExt = 7;  // Demande de l'utilisatuer à l'extérieur

// Capteurs infrarouges
short capteurRecep = 3;  // Detecter l'objet
short capteurEme = 6;    // Capteur emetteur

// Moteur
short moteurOuv = 8;
short moteurFerm = 9;

// Initialiser les différents capteurs
void InitialisationCapteurs() {
  myCapteurs.SetOutputPin(capteurEme, ledPortail, moteurOuv, moteurFerm);
  myCapteurs.SetInputPin(captOuvert, captFerme, capteurRecep, bPInt, bPExt);

  // Activer le capteur infrarouge
  myCapteurs.WriteOn(capteurEme);

  // Arreter le moteur
  myCapteurs.WriteOff(moteurOuv);
  myCapteurs.WriteOff(moteurFerm);

  // KeyPad
  KeyPad.begin(9600);

  // Initialiser LED
  myLED.LED(ledPortail);
}

// Vérifier les différents capteurs
void VerificationCapteurs() {
  demande = digitalRead(bPInt) || demandeExtAccept;  // Détecter quand l'utilisateur demande le changement d'état

  LireEtAppliquer(capteurRecep, &objetDetecte);  // Quand un objet est détecté
  LireEtAppliquer(captOuvert, &portailOuvert);   // Capteur d'ouverture / Portail Ouvert
  LireEtAppliquer(captFerme, &portailFermer);    // Capteur de fermeture / Portail Fermer
}


// Lire le capteur en digitalRead et appliquer le résultat à la variable
void LireEtAppliquer(short capteur, bool* variable) {
  *variable = digitalRead(capteur);
}