#include "Arduino.h"
#include "Capteurs.h"

// Mettre les capteurs en 
  void Capteurs::SetOutputPin(int pin1 = -1, int pin2 = -1, int pin3 = -1, int pin4 = -1, int pin5 = -1, int pin6 = -1, int pin7 = -1, int pin8 = -1)
  {
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
    pinMode(pin5, OUTPUT);
    pinMode(pin6, OUTPUT);
    pinMode(pin7, OUTPUT);
    pinMode(pin8, OUTPUT);
  }
 // Mettre les capteurs en entrée
  void Capteurs::SetInputPin(int pin1 = -1, int pin2 = -1, int pin3 = -1, int pin4 = -1, int pin5 = -1, int pin6 = -1, int pin7 = -1, int pin8 = -1)
  {
    pinMode(pin1, INPUT);
    pinMode(pin2, INPUT);
    pinMode(pin3, INPUT);
    pinMode(pin4, INPUT);
    pinMode(pin5, INPUT);
    pinMode(pin6, INPUT);
    pinMode(pin7, INPUT);
    pinMode(pin8, INPUT);
  }

// Activer les capteurs
void Capteurs::WriteOn(int nb1 = -1, int nb2 = -1, int nb3 = -1, int nb4 = -1, int nb5 = -1, int nb6 = -1, int nb7 = -1, int nb8 = -1)
{
  digitalWrite(nb1, true);
  digitalWrite(nb2, true);
  digitalWrite(nb3, true);
  digitalWrite(nb4, true);
  digitalWrite(nb5, true);
  digitalWrite(nb6, true);
  digitalWrite(nb7, true);
  digitalWrite(nb8, true);
}

// Désactiver les capteurs
void Capteurs::WriteOff(int nb1 = -1, int nb2 = -1, int nb3 = -1, int nb4 = -1, int nb5 = -1, int nb6 = -1, int nb7 = -1, int nb8 = -1)
{
  digitalWrite(nb1, false);
  digitalWrite(nb2, false);
  digitalWrite(nb3, false);
  digitalWrite(nb4, false);
  digitalWrite(nb5, false);
  digitalWrite(nb6, false);
  digitalWrite(nb7, false);
  digitalWrite(nb8, false);
}