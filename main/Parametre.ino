// Ici réside les actions répétitive qui peuvent être réduit

// Ecrire dans le serial
bool Printer(String texte)
{
  Serial.print(texte);
  return true;
}

 // Ecrire dans le Serial avec un saut de ligne 
bool Printforln(String texte)
{
  Serial.println(texte);
  return true;
}

// Avoir le temps passé en prenant l'horloge d'arduino comme référence
long TimeForCurrentMillis(long value) 
{
  return currentMillis - value;
}
// Délais inférieur à la valeur max
bool TimerBelow(long tempsActuel, long tempsMax)
{
  return TimeForCurrentMillis(tempsActuel) < tempsMax; // Le timer est inférieur
}

