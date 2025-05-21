// Le moteur se met en marche pour fermer le portail
void FermetureMoteur() {
  LCDFermeture();  // Afficher Fermeture
  // Sens de déplacement : fermeture
  myCapteurs.WriteOn(moteurFerm);
  myCapteurs.WriteOff(moteurOuv);
}

// Le moteur se met en marche pour ouvrir le portail
void OuvertureMoteur() {
  LCDOuverture();  // Afficher Ouverture
  // Sens de déplacement : ouverture
  myCapteurs.WriteOn(moteurOuv);
  myCapteurs.WriteOff(moteurFerm);
}

// Activer le moteur vers la droite (true) ou vers la gauche (false)
bool MoteurStart(bool fermeture) {
  moteurWork = true; // Le moteur est en marche 
  // Demande de fermeture
  if (fermeture) {
    FermetureMoteur();
    return true;
  }
  OuvertureMoteur();
  return true;
}

// Avoir l'état du moteur
bool MoteurState() {
  return moteurWork;
}

// Arrêter le moteur
bool MoteurStop() {
  MDPInputValueReset();  // L'utilisateur ne veux plus taper le MPD

  moteurWork = false;

  // Arrêter moteur
  myCapteurs.WriteOff(moteurFerm, moteurOuv);
  return true;
}