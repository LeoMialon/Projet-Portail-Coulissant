#ifndef Parametre_H
#define Parametre_H

#include "Arduino.h"


// Ici réside les actions répétitive qui peuvent être réduit
class Parametre {
  public:
  // Ecrire dans le serial
  bool Print(String texte = "");

  // Ecrire dans le Serial avec un saut de ligne
  bool Println(String texte = "");
  // Délais inférieur à la valeur max
  bool TimerBelow(long tempsActuel, long tempsMax, long currentMillis);

  private : 
  // Avoir le temps passé en prenant l'horloge d'arduino comme référence
  long TimeForCurrentMillis(long value, long currentMillis);


};




#endif