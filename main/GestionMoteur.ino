
// Activer le moteur vers la droite (true) ou vers la gauche (false)
bool MoteurStart(bool direction)
{
  moteurWork = true;
  if(direction)
  {
    LCDFermeture(); // Afficher Fermeture
    Serial.println("Fermeture en cours");
    // Sens de déplacement : fermeture
    digitalWrite(moteurFerm, true);
    digitalWrite(moteurOuv, false);

    return true;
  }

  LCDOuverture(); // Afficher Ouverture
  Serial.println("Ouverture en cours");
  // Sens de déplacement : ouverture
  digitalWrite(moteurOuv, true);
  digitalWrite(moteurFerm, false);
  return true;

}

// Avoir l'état du moteur
bool MoteurState() { return moteurWork;}

// Arrêter le moteur
bool MoteurStop()
{
  Serial.println("Arret en cours");
  
  MDPInputValueReset(); // L'utilisateur ne voulait plus taper le MPD


  moteurWork = false;
  // Arrêter moteur
  digitalWrite(moteurFerm, false);
  digitalWrite(moteurOuv, false);
  return true;
}