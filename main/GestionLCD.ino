
// Démarrer écran LCD
void LCDStart() {
  lcd.begin(16, 2);
  lcd.display();
}

// Afficher le texte voulue à l'endroit souhaité
void PTexte(String texte = "", int curseur = 0, int ligne = 0) {
  lcd.setCursor(curseur, ligne);
  lcd.print(texte);
}

// Effacer l'écran et afficher le texte voulue à l'endroit indiqué
void CPTexte(String texte = "", int curseur = 0, int ligne = 0) {
  lcd.clear();
  PTexte(texte, curseur, ligne);
}

// Afficher le texte "Mot de passe" à la ligne voulue
void PMDP(int ligne = 0) {
  CPTexte("Mot de passe", 2, ligne);
}

// Afficher portail fermer
void LCDFermer() {
  CPTexte("Portail", 5);
  PTexte("Fermer", 6, 1);
}

// Afficher portail ouvert
void LCDOuvert() {
  CPTexte("Portail", 5);
  PTexte("Ouvert", 5, 1);
}


// Afficher Fermeture
void LCDFermeture() {
  CPTexte("Fermeture", 3);
}

// Afficher Ouverture
void LCDOuverture() {
  CPTexte("Ouverture", 3);
}

// Afficher arret d'urgence
void LCDStop() {
  CPTexte(";)", 4);
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
  PTexte("Creer votre", 2, 0);
}

// Afficher la confirmation de la création du MDP
void LCDMDPCreated() {
  PMDP();
  PTexte("cree", 3, 1);
}

// Quand le MDP taper est juste
void LCDMDPTrue() {
  PMDP();
  PTexte("Vrai", 6, 1);
}

// Quand le MDP taper est faux
void LCDMDPFalse() {
  PMDP();
  PTexte("Faux", 6, 1);
}

// Afficher Taper Mot de passe
void LCDInputMDP() {
  PMDP(1);
  PTexte("Taper", 6);
}

// Afficher MDP remis à zéro
void LCDMDPMotDePasseReset(){
  PMDP();
  PTexte("Remis a zero", 2, 1);
}