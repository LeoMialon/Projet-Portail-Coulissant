// Led 
int ledPortail = 4; // Activation de la led

// Capteurs FDC 
int captOuvert = 5; // Capteur Ouverture
int captFerme = A2; // Capteur Fermeture

// Bouton Poussoirs 
int bPInt = 2; // Demande de l'utilisateur à l'intérieur 
int bPExt = 7; // Demande de l'utilisatuer à l'extérieur 

// Capteurs infrarouges 
int capteurRecep = 3; // Detecter l'objet 
int capteurEme = 6; // Capteur emetteur 

// Moteur 
int moteurOuv = 8;
int moteurFerm = 9;

// Initialiser les différents capteurs
void CapteurInitialisation()
{
  pinMode(capteurEme, OUTPUT); // Capteur emmeteur infrarouge
  pinMode(ledPortail, OUTPUT); // LED

  // Moteur 
  pinMode(moteurOuv, OUTPUT); 
  pinMode(moteurFerm, OUTPUT);

  // Capteur fin de course
  pinMode(captOuvert, INPUT);
  pinMode(captFerme, INPUT);

  // Boutons poussoirs
  pinMode(bPInt, INPUT);
  pinMode(bPExt, INPUT);

  // Capteurs infrarouges
  pinMode(capteurRecep, INPUT);

  // Activer le capteur infrarouge
  WriteOn(capteurEme); 
  
  // Arreter le moteur
  WriteOff(moteurOuv); 
  WriteOff(moteurFerm);  

  // KeyPad
  KeyPad.begin(9600); 
}

// Vérifier les différents capteurs
void CapteurVerification()
{
  demande = digitalRead(bPInt) || demandeExtAccept; // Détecter quand l'utilisateur demande le changement d'état
  objetDetecte = digitalRead(capteurRecep); // Quand un objet est détecté
  capteurOuvert = digitalRead(captOuvert); // Capteur d'ouverture / Portail Ouvert
  capteurFerme = digitalRead(captFerme); // Capteur de fermeture / Portail Fermer
}

// Activer le capteur 
bool WriteOn(short nb)
{
  digitalWrite(nb, true);
  return true;
}

// Désactiver le capteur
bool WriteOff(short nb)
{
  digitalWrite(nb, false);
  return false;
}