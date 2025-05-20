
// Activer le moteur vers la droite (true) ou vers la gauche (false)
bool MoteurStart(bool direction)
{
  moteurWork = true;

  // Demande de fermeture
  if(direction)
  {
    LCDFermeture(); // Afficher Fermeture
    // Sens de déplacement : fermeture
    myCapteurs.WriteOn(moteurFerm);
    myCapteurs.WriteOff(moteurOuv);

    return true;
  }

  LCDOuverture(); // Afficher Ouverture
  // Sens de déplacement : ouverture
  myCapteurs.WriteOn(moteurOuv);
  myCapteurs.WriteOff(moteurFerm);
  return true;

}

// Avoir l'état du moteur
bool MoteurState() { return moteurWork;}

// Arrêter le moteur
bool MoteurStop()
{  
  MDPInputValueReset(); // L'utilisateur ne veux plus taper le MPD

  moteurWork = false;

  // Arrêter moteur
  myCapteurs.WriteOff(moteurFerm, moteurOuv);
  return true;
}