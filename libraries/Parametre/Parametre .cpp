#include "Arduino.h"
#include "Parametre.h"

  bool Parametre::Print(String texte = "") {
    Serial.print(texte);
    return true;
  }
  bool Parametre::Println(String texte = "") {
    Serial.println(texte);
    return true;
  }
  long Parametre::TimeForCurrentMillis(long value, long currentMillis) {
    return currentMillis - value;
  }
  bool Parametre::TimerBelow(long tempsActuel, long tempsMax, long currentMillis) {
    return TimeForCurrentMillis(tempsActuel, currentMillis) < tempsMax;  // Le timer est inférieur
  }

  void Parametre::SetOutputPin(int pin1 = -1, int pin2 = -1, int pin3 = -1, int pin4 = -1, int pin5 = -1, int pin6 = -1, int pin7 = -1, int pin8 = -1)
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

  void Parametre::SetInputPin(int pin1 = -1, int pin2 = -1, int pin3 = -1, int pin4 = -1, int pin5 = -1, int pin6 = -1, int pin7 = -1, int pin8 = -1)
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