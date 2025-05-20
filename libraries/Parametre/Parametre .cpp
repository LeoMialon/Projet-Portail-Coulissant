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
    return Parametre::TimeForCurrentMillis(tempsActuel, currentMillis) < tempsMax;  // Le timer est inférieur
  }

