// Peut être changer par l'ajout de texte dans un mot
String motDePasseTaper = ""; // MotDePasse taper par l'utilisateur
String MotDePasseValue = ""; // MotDePasse Sauvegarder par le système

bool MotDePasseCreate = false;
bool MotDePasse = false;
bool MotDePasseInput = false;
long count;

const long timerMotDePasse = 10000;       // Temps durant lequel le MotDePasse est actif 60s
const long timerInputMotDePasse = 20000;  // temps durant lequel l'utilisateur peux entrer le MotDePasse 20s
long countMotDePasse = 0;                 // Variable pour compter le temps passé 

const long timerDelayInput = 10000;  // Temps durant lequel l'utilisateur peux taper un numéro de son code 10s
int KeyPadNumber = -1;  // Nombre taper sur le Keypad
int wantHelp = 0; // L'utilisateur a besoin d'aide 


// Condition du mot de passe
bool MotDePasseVerification() {

  long currentMilli = currentMillis;  // Mise à jour de la valeur currentMilli
  count = currentMilli - countMotDePasse;
  KeyPadNumber = SetNumberPad();  // Avoir une valeur si le l'utilisateur utilise le keypad
  if(wantHelp >= 3) // L'utilisateur ne se rapelle plus du MotDePasse
  {
    ResetTimer(&countMotDePasse);  // Remettre le compteur à 0
    RemoveMotDePasse(); // Effacer le MotDePasse taper par l'utilisateur
    EffacerMoteDePasse(); 

    AfficherMotDePasse();; // Mettre à jour l'affichage du texte
    
  }
  // Quand l'utilisateur peux taper un MotDePasse
  if (MotDePasseInput) {
    // Taper le MotDePasse et vérifier s'il est bon
    if (!MotDePasseCreate && VerifierCreationMotDePasse()) {
      Par.Println("Yahoo");
      MotDePasseCreate = true;
      MotDePasse = true;
      return true;
    }

    if (TimerEndReset())  // Trop de temps pour taper le MotDePasse : terminer la procédure
    {
      Par.Println("Reset");
      MotDePasseInputValueReset();  // L'utilisateur ne tape plus de MotDePasse
      LCDDisplay();          // Affciher l'état actuel du portail
    }

    else if(MotDePasseCreate && VerifierMotDePasse())
    {
      MotDePasse = true;
      return true;
    }
    
  }

  // Si le MotDePasse est actif mais que le timer est écoulé
  if (MotDePasse && count > timerMotDePasse) {
    MotDePasse = false;           // Il faut retaper le MotDePasse
    MotDePasseInputValueReset();  // L'utilisateur ne tape plus de MotDePasse
    Par.Println("Le Mot de passe n'est plus valide");
    ResetTimer(&countMotDePasse); // Remettre le compteur à 0
  }

  if (digitalRead(bPExt)) {  // Vérifier si le bouton extérieur est pressé
    if (MotDePasseInputStart()) return true;
    ResetTimer(&countMotDePasse);  // Remettre le compteur à 0
    RemoveMotDePasse(); // Effacer le MotDePasse taper par l'utilisateur
  }

  return false;
}

// Vérifier si le Mot de passe est taper en entier, à la création
bool VerifierCreationMotDePasse() {
  // On regarde Ce qu'à écrit l'utilisateur
  if (UserKeypadUse() && motDePasseTaper.length() == 6) {
    MotDePasseValue = motDePasseTaper; // On initialise le MotDePasse
    LCDMotDePasseCreated();
    return true;
  }

  return false;
}

// On regarde Ce qu'à écrit l'utilisateur et s'il tape un nombre : ajouter à la liste
bool VerifierMotDePasse() {
  if (UserKeypadUse() && motDePasseTaper.length() == 6) {
    if (Equal(motDePasseTaper, MotDePasseValue))  // On compare le MotDePasse taper par l'utilisateur avec le MotDePasse sauvegardé
    {
      Par.Println("MotDePasse correct");
      LCDMotDePasseTrue();  // Afficher que le MotDePasse est bon
      MotDePasseInputValueReset(); // Remettre le MotDePasse à zéro
      return true;
    } else  // Le MotDePasse est mauvais
    {
      LCDMotDePasseFalse();         // Afficher que le MotDePasse est mauvais
      MotDePasseInputValueReset();  // Remettre à zéro valeurs
    }
  }
  return false;
}

// Rénitialiser le compteur
void ResetTimer(long* timer) {
  *timer = currentMillis;  // Rénitialise la valeur indiqué
}

// Quand l'utilisateur appuis sur le bouton sans avoir activer le MotDePasse
bool MotDePasseInputStart() {
  if (MotDePasse)        // Vérifier si le MotDePasse est actif
    return true;  // Faire bouger le portail

  if(!MotDePasseInput)
    AfficherMotDePasse();
  
  MotDePasseInput = true;
  return false;
}

// L'utilisateur ne veux / peux plus taper le MotDePasse
void MotDePasseInputValueReset() {
  MotDePasseInput = false;
  RemoveMotDePasse();  // Effacer la suite de chiffres que l'utilisateurs était en train de taper
}

// L'utilisateur n'a pas le temps de taper son MotDePasse : Fin de la procédure
bool TimerEndReset() {
  if (count > timerInputMotDePasse)
    return true;
  // Temps trop long pour taper une touche : 10s
  if (motDePasseTaper != "" && count > timerDelayInput)
    return true;

   // Temps trop long pour taper une touche : 10s
  if(motDePasseTaper.length() > 0 && count > timerDelayInput)
    return true;
  
  return false;
}

// Ajoute à la liste un nombre
bool UserKeypadUse() {
  if (KeypadUse()) {
    AddToCurrentMotDePasse(); // Ajouter le nombre au MotDePasse tapé
  }
  return KeypadUse();
}

// Comparé 2 vecteurs
bool Equal(String string1, String string2) {
  return string1.equals(string2);
}

// Ajouter le nombre au MotDePasse
bool AddToCurrentMotDePasse()
{
  motDePasseTaper += KeyPadNumber;  // Ajouter le chiffre à la suite
  Par.Print("KeyPadNumber: ");
  Par.Println((String)motDePasseTaper.length());
  ResetTimer(&countMotDePasse);
  return true;
}

// Remettre le MotDePasse taper par l'utilisateur à zéro
void RemoveMotDePasse()
{
  motDePasseTaper = ""; // Remettre le MotDePasse taper par l'utilisateur à zéro
  wantHelp = 0; // L'utilisateur ne veux pas d'aide 
}

// Afficher le texte que voit l'utilisateur quand t'il appuis sur le bouton Exterieur
void AfficherMotDePasse()
{
  if (MotDePasseCreate) LCDInputMotDePasse();  // afficher que l'utilisateur doit taper le MotDePasse
  else LCDSetMotDePasse(); // afficher le texte de création de MotDePasse
}

// Effacer le mot de passe dans les données
void EffacerMoteDePasse()
{
  motDePasseTaper = ""; // Effacer le Mot de passe actuel 
  MotDePasseValue = ""; // Effacer le mot de passe enregistré
  MotDePasseCreate = false; // Dire que le MotDePasse n'est plus là 
}
