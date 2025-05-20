
// Afficher le texte "Mot de passe" à la ligne voulue
void PMDP(int ligne = 0) {
  myLCD.CPTexte("Mot de passe", 2, ligne);
}

// Afficher portail fermer
void LCDFermer() {
  myLCD.CPTexte("Portail", 5);
  myLCD.PTexte("Fermer", 6, 1);
}

// Afficher portail ouvert
void LCDOuvert() {
  myLCD.CPTexte("Portail", 5);
  myLCD.PTexte("Ouvert", 5, 1);
}


// Afficher Fermeture
void LCDFermeture() {
  myLCD.CPTexte("Fermeture", 3);
}

// Afficher Ouverture
void LCDOuverture() {
  myLCD.CPTexte("Ouverture", 3);
}

// Afficher arret d'urgence
void LCDStop() {
  myLCD.CPTexte(";)", 4);
}

// Afficher texte pour l'état correspondant
void LCDDisplay() {
  if (capteurFerme) { LCDFermer(); }  // Afficher fermer
  else if (capteurOuvert) {
    LCDOuvert();
  }                                               // Afficher ouvert
  else if (ouvertureEnCours) { LCDOuverture(); }  // Afficher ouverture
  else if (fermetureEnCours) {
    LCDFermeture();
  }  // Afficher fermeture
}

// Afficher pour la création du MDP
void LCDSetMDP() {
  PMDP(1);
  myLCD.PTexte("Creer votre", 2, 0);
}

// Afficher la confirmation de la création du MDP
void LCDMDPCreated() {
  PMDP();
  myLCD.PTexte("cree", 3, 1);
}

// Quand le MDP taper est juste
void LCDMDPTrue() {
  PMDP();
  myLCD.PTexte("Vrai", 6, 1);
}

// Quand le MDP taper est faux
void LCDMDPFalse() {
  PMDP();
  myLCD.PTexte("Faux", 6, 1);
}

// Afficher Taper Mot de passe
void LCDInputMDP() {
  PMDP(1);
  myLCD.PTexte("Taper", 6);
}

// Afficher MDP remis à zéro
void LCDMDPMotDePasseReset(){
  PMDP();
  myLCD.PTexte("Remis a zero", 2, 1);
}