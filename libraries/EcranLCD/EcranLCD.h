#ifndef EcranLCD_H
#define EcranLCD_H

#include "Arduino.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include "Parametre.h"

// Commande et initialisation d'un écran LCD
class CommandeLCD {
  public:

  // Initialiser l'écran LCD
  LCD();
  // Effacer le texte du LCD
  void Clear();
  // Afficher le texte voulue à l'endroit souhaité
  void PTexte(String texte = "", int curseur = 0, int ligne = 0);
  // Effacer l'écran et afficher le texte voulue à l'endroit indiqué
  void CPTexte(String texte = "", int curseur = 0, int ligne = 0);


  private:
  Parametre Par;
  rgb_lcd myLCD;
  // Démarrer écran LCD
  void LCDStart();

};




#endif