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

  Par.SetOutputPin(capteurEme, ledPortail, moteurOuv, moteurFerm);
  Par.SetInputPin(captOuvert, captFerme, capteurRecep, bPInt, bPExt);
  
  // Activer le capteur infrarouge
  WriteOn(capteurEme); 
  
  // Arreter le moteur
  WriteOff(moteurOuv); 
  WriteOff(moteurFerm);  

  // KeyPad
  KeyPad.begin(9600);

  // Initialiser LED
  myLED.LED(ledPortail); 
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