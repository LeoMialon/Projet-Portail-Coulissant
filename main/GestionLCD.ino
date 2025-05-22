// Initialiser LCD
void InitialisationLCD()
{
  myLCD.LCD();
}


// Afficher le texte "Mot de passe" à la ligne voulue
void PMotDePasse(int ligne = 0) {
  myLCD.CPTexte("Mot de passe", 2, ligne);
}

// Afficher le texte "Portail" à la ligne voulue
void PPortail(int ligne = 0){
  myLCD.CPTexte("Portail", 5, ligne);
}

// Afficher portail fermer
void LCDFermer() {
  PPortail();
  myLCD.PTexte("Fermer", 6, 1);
}

// Afficher portail ouvert
void LCDOuvert() {
  PPortail();
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
  myLCD.CPTexte(";)", 7);
}

// Afficher texte pour l'état correspondant
void LCDDisplay() {
  if (portailFermer) { LCDFermer(); }  // Afficher fermer
  else if (portailOuvert) {
    LCDOuvert();
  }                                               // Afficher ouvert
  else if (ouvertureEnCours) { LCDOuverture(); }  // Afficher ouverture
  else if (fermetureEnCours) {
    LCDFermeture();
  }  // Afficher fermeture
}

// Afficher pour la création du MotDePasse
void LCDSetMotDePasse() {
  PMotDePasse(1);
  myLCD.PTexte("Creer votre", 2, 0);
}

// Afficher la confirmation de la création du MotDePasse
void LCDMotDePasseCreated() {
  PMotDePasse();
  myLCD.PTexte("cree", 3, 1);
}

// Quand le MotDePasse taper est juste
void LCDMotDePasseTrue() {
  PMotDePasse();
  myLCD.PTexte("Vrai", 6, 1);
}

// Quand le MotDePasse taper est faux
void LCDMotDePasseFalse() {
  PMotDePasse();
  myLCD.PTexte("Faux", 6, 1);
}

// Afficher Taper Mot de passe
void LCDInputMotDePasse() {
  PMotDePasse(1);
  myLCD.PTexte("Taper", 6);
}

// Afficher MotDePasse remis à zéro
void LCDMotDePasseMotDePasseReset(){
  PMotDePasse();
  myLCD.PTexte("Remis a zero", 2, 1);
}