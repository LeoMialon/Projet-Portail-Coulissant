#ifndef Capteurs_H
#define Capteurs_H

#include "Arduino.h"


// Ici réside les actions répétitive qui peuvent être réduit
class Capteurs {

  public:
  // Mettre les pins en sortie
  void SetOutputPin(int pin1 = -1, int pin2 = -1, int pin3 = -1, int pin4 = -1, int pin5 = -1, int pin6 = -1, int pin7 = -1, int pin8 = -1);
  
  // Mettre les pins en entrée
  void SetInputPin(int pin1 = -1, int pin2 = -1, int pin3 = -1, int pin4 = -1, int pin5 = -1, int pin6 = -1, int pin7 = -1, int pin8 = -1);

  // Désactiver le capteur
  void WriteOff(int nb1 = -1, int nb2 = -1, int nb3 = -1, int nb4 = -1, int nb5 = -1, int nb6 = -1, int nb7 = -1, int nb8 = -1);

  // Activer le capteur
  void WriteOn(int nb1 = -1, int nb2 = -1, int nb3 = -1, int nb4 = -1, int nb5 = -1, int nb6 = -1, int nb7 = -1, int nb8 = -1);

};




#endif