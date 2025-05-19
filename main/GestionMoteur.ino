
// Activer le moteur vers la droite (true) ou vers la gauche (false)
bool MoteurStart(bool direction)
{
  moteurWork = true;

  // Demande de fermeture
  if(direction)
  {
    LCDFermeture(); // Afficher Fermeture
    // Sens de déplacement : fermeture
    WriteOn(moteurFerm);
    WriteOff(moteurOuv);

    return true;
  }

  LCDOuverture(); // Afficher Ouverture
  // Sens de déplacement : ouverture
  WriteOn(moteurOuv);
  WriteOff(moteurFerm);
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
  WriteOff(moteurFerm);
  WriteOff(moteurOuv);
  return true;
}