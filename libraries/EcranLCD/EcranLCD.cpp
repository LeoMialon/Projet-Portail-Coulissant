#include "Arduino.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include "Parametre.h"
#include "EcranLCD.h"

// intialiser myLCD 
CommandeLCD::LCD()
{
  LCDStart();
}

// Démarrer écran LCD
void CommandeLCD::LCDStart() {
  myLCD.begin(16, 2);
  myLCD.display();
  Clear();
}

// Effacer le texte du LCD
void CommandeLCD::Clear()
{
  myLCD.clear(); // Effacer le texte du LCD
  Par.Println(); // Debug
}

// Afficher le texte voulue à l'endroit souhaité
void CommandeLCD::PTexte(String texte = "", int curseur = 0, int ligne = 0) {
  myLCD.setCursor(curseur, ligne); // Placement à l'endroit voulue
  myLCD.print(texte); // Ecrire le texte

  Par.Print(texte); // Debug
  Par.Println(); // Debug
}

// Effacer l'écran et afficher le texte voulue à l'endroit indiqué
void CommandeLCD::CPTexte(String texte = "", int curseur = 0, int ligne = 0) {
  Clear(); // Effacer le texte du LCD
  PTexte(texte, curseur, ligne); // Afficher le texte voulue à l'endroit souhaité
}
