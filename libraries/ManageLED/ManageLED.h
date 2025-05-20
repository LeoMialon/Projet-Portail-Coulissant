#ifndef ManageLED_H
#define ManageLED_H

#include "Arduino.h"

// Commandes et initialisation d'une LED
class GestionLED {
  public:
  // intialiser LED et delais
  LED(short _pinLED);
  // Savoir si la LED est active
  bool LedOn(bool moteurState, bool capteurs, long currentMillis);
  // Activer la LED
  void ActiverLED(bool moteurState, bool capteurs, long currentMillis);
  // Mettre le compteur à la valeur voulue
  void SetCompteurLED(long value);

  private:
  short pinLED;
  int delaisActivationMoteurMarche;
  int delaisActivationMoteurArret;
  long compteurLED; 
  int tempsDelaisLED;


};




#endif