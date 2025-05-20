// Peut être changer par l'ajout de texte dans un mot
String currentMDPInput = ""; // MDP taper par l'utilisateur
String MDPValue = ""; // MDP Sauvegarder par le système

bool MDPCreate = false;
bool MDP = false;
bool MDPInput = false;
long count;

const long timerMDP = 10000;       // Temps durant lequel le MDP est actif 60s
const long timerInputMDP = 20000;  // temps durant lequel l'utilisateur peux entrer le MDP 20s
long countMDP = 0;                 // Variable pour compter le temps passé 

const long timerDelayInput = 10000;  // Temps durant lequel l'utilisateur peux taper un numéro de son code 10s
int KeyPadNumber = -1;  // Nombre taper sur le Keypad
int wantHelp = 0; // L'utilisateur a besoin d'aide 


// Condition du mot de passe
bool MDPVerification() {

  long currentMilli = currentMillis;  // Mise à jour de la valeur currentMilli
  count = currentMilli - countMDP;
  KeyPadNumber = SetNumberPad();  // Avoir une valeur si le l'utilisateur utilise le keypad
  if(wantHelp >= 3) // L'utilisateur ne se rapelle plus du MDP
  {
    MDPInput = false;
    MDPValue = ""; // Remettre à zéro le MDP
    MDPCreate = false; // Dire que le MDP n'est plus là 
  }
  // Quand l'utilisateur peux taper un MDP
  if (MDPInput) {
    // Taper le MDP et vérifier s'il est bon
    if (!MDPCreate && VerifierCreationMDP()) {
      Par.Println("Yahoo");
      MDPCreate = true;
      MDP = true;
      return true;
    }

    if (TimerEndReset())  // Trop de temps pour taper le MDP : terminer la procédure
    {
      Par.Println("Reset");
      MDPInputValueReset();  // L'utilisateur ne tape plus de MDP
      LCDDisplay();          // Affciher l'état actuel du portail
    }

    else if(MDPCreate && VerifierMDP())
    {
      MDP = true;
      return true;
    }
    
  }

  // Si le MDP est actif mais que le timer est écoulé
  if (MDP && count > timerMDP) {
    MDP = false;           // Il faut retaper le MDP
    MDPInputValueReset();  // L'utilisateur ne tape plus de MDP
    Par.Println("Le Mot de passe n'est plus valide");
    ResetTimer(&countMDP); // Remettre le compteur à 0
  }

  if (digitalRead(bPExt)) {  // Vérifier si le bouton extérieur est pressé
    if (MDPInputStart()) return true;
    ResetTimer(&countMDP);  // Remettre le compteur à 0
    RemoveMDP(); // Effacer le MDP taper par l'utilisateur
  }

  return false;
}

bool VerifierCreationMDP() {
  // On regarde Ce qu'à écrit l'utilisateur

  if (UserKeypadUse() && currentMDPInput.length() == 6) {
    MDPValue = currentMDPInput; // On initialise le MDP
    LCDMDPCreated();
    return true;
  }

  return false;
}

bool VerifierMDP() {

  // On regarde Ce qu'à écrit l'utilisateur et s'il tape un nombre ajouter à la liste et L'utilisateur a taper un MDP
  if (UserKeypadUse() && currentMDPInput.length() == 6) {
    if (Equal(currentMDPInput, MDPValue))  // On compare le MDP taper par l'utilisateur avec le MDP sauvegardé
    {
      Par.Println("MDP correct");
      LCDMDPTrue();  // Afficher que le MDP est bon
      MDPInputValueReset(); // Remettre le MDP à zéro
      return true;
    } else  // Le MDP est mauvais
    {
      LCDMDPFalse();         // Afficher que le MDP est mauvais
      MDPInputValueReset();  // Remettre à zéro valeurs
    }
  }
  return false;
}

// Rénitialiser le compteur
void ResetTimer(long* timer) {
  *timer = currentMillis;  // Rénitialise la valeur indiqué
}

// Quand l'utilisateur appuis sur le bouton sans avoir activer le MDP
bool MDPInputStart() {
  if (MDP)        // Vérifier si le MDP est actif
    return true;  // Faire bouger le portail

  if (MDPValue != "") LCDInputMDP();  // afficher que l'utilisateur doit taper le MDP
  else LCDSetMDP(); // afficher le texte de création de MDP
  MDPInput = true;
  return false;
}

// L'utilisateur ne veux / peux plus taper le MDP
void MDPInputValueReset() {
  MDPInput = false;
  RemoveMDP();  // Effacer la suite de chiffres que l'utilisateurs était en train de taper
}

// L'utilisateur n'a pas le temps de taper son MDP : Fin de la procédure
bool TimerEndReset() {
  if (count > timerInputMDP)
    return true;
  // Temps trop long pour taper une touche : 10s
  if (currentMDPInput != "" && count > timerDelayInput)
    return true;

   // Temps trop long pour taper une touche : 10s
  if(currentMDPInput.length() > 0 && count > timerDelayInput)
    return true;
  
  return false;
}

// Ajoute à la liste un nombre
bool UserKeypadUse() {
  if (KeypadUse()) {
    AddToCurrentMDP(); // Ajouter le nombre au MDP tapé
  }
  return KeypadUse();
}

// Comparé 2 vecteurs
bool Equal(String string1, String string2) {
  return string1.equals(string2);
}

bool AddToCurrentMDP()
{
  currentMDPInput += KeyPadNumber;  // Ajouter le chiffre à la suite
  Par.Print("KeyPadNumber: ");
  Par.Println((String)currentMDPInput.length());
  ResetTimer(&countMDP);
  return true;
}

// Remettre le MDP taper par l'utilisateur à zéro
void RemoveMDP()
{
  currentMDPInput = ""; // Remettre le MDP taper par l'utilisateur à zéro
  wantHelp = 0; // L'utilisateur ne veux pas d'aide 
}
