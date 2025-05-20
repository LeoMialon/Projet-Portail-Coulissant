#ifndef Parametre_H
#define Parametre_H

#include "Arduino.h"


// Ici réside les actions répétitive qui peuvent être réduit
class Parametre {
  protected: 
  // Avoir le temps passé en prenant l'horloge d'arduino comme référence
  long TimeForCurrentMillis(long value, long currentMillis);

  public:
  // Ecrire dans le serial
  bool Print(String texte = "");

  // Ecrire dans le Serial avec un saut de ligne
  bool Println(String texte = "");

  // Délais inférieur à la valeur max
  bool TimerBelow(long tempsActuel, long tempsMax, long currentMillis);
  
  // Mettre les pins en sortie
  void SetOutputPin(int pin1 = -1, int pin2 = -1, int pin3 = -1, int pin4 = -1, int pin5 = -1, int pin6 = -1, int pin7 = -1, int pin8 = -1);
  
  // Mettre les pins en entrée
  void SetInputPin(int pin1 = -1, int pin2 = -1, int pin3 = -1, int pin4 = -1, int pin5 = -1, int pin6 = -1, int pin7 = -1, int pin8 = -1);


};




#endif