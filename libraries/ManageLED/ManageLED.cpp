#include "Arduino.h"
#include "ManageLED.h"

// intialiser LED et delais
GestionLED::LED(short _pinLED)
{
  pinLED = _pinLED;
  delaisActivationMoteurMarche = 100; // Temps d'activation et de désactivation de la LED à 100ms
  delaisActivationMoteurArret = 400; // temps d'activation et de désactivation de la LED à 400ms
  compteurLED = 0;
  tempsDelaisLED = 0;
}

// Savoir si la LED est active
bool GestionLED::LedOn(bool moteurState, bool capteurs, long currentMillis)
{
  if(moteurState) // Si le portail est en marche
    tempsDelaisLED = delaisActivationMoteurMarche; // Fréquence de la LED mis à 100ms : Portail bouge
  else
    tempsDelaisLED = delaisActivationMoteurArret; // Fréquence de la LED mis à 400ms : Portail à l'arrêt

  if(capteurs) // Si le portail est à l'arrêt
    return false;

  if (currentMillis - compteurLED <= tempsDelaisLED) // Entre 0 et 400 milli la LED est allumé 
    return true;
  if(currentMillis - compteurLED <= tempsDelaisLED*2) // Entre 400 et 800 milli la LED est eteinte
    return false;
  
  // Reset compteurLED
  compteurLED = currentMillis;
  return true;
}

// Activer la LED
void GestionLED::ActiverLED(bool moteurState, bool capteurs, long currentMillis)
{
  digitalWrite(pinLED, LedOn(moteurState, capteurs, currentMillis));
}

// Mettre le compteur à la valeur voulue
void GestionLED::SetCompteurLED(long value) { compteurLED = value;}