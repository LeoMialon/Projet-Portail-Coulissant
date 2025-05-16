// Activer la LED
void LEDActivation()
{
  digitalWrite(ledPortail, LedOn());
}


// Activation de la LED
bool LedOn()
{
  if(MoteurState()) // Si le portail est en marche
    countTimerLed = countTimerLedChange; // Fréquence de la LED mis à 100ms : Portail bouge
  else
    countTimerLed = countTimerLedStop; // Fréquence de la LED mis à 400ms : Portail à l'arrêt

  if(capteurs) // Si le portail est à l'arrêt
    return false;

  if (currentMillis - timerLed <= countTimerLed) // Entre 0 et 400 milli la LED est allumé 
    return true;
  if(currentMillis - timerLed <= countTimerLed*2) // Entre 400 et 800 milli la LED est eteinte
    return false;
  
  // Reset timerLED
  timerLed = currentMillis;
  return true;
}