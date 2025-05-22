String motDuRasberry = "";

// Lire ce qui arrive du RasberryPi
bool ReadRasberryPi(String* value) {

  // On vérifie si une donnée est envoyé
  if(Serial.available())
    *value += Serial.readString();  // On lit le mot envoyé par le RasberryPi avec le délais TimeOut : voir Setup()
  else *value = "";

  return *value != "";
}


// Voir s'il y a une donnée envoyé par le rasberryPi et réagir en conséquence
bool CheckRasberryPi() {

  // Si le Rasberry envoit une donnée
  if (ReadRasberryPi(&motDuRasberry)) {
    motDuRasberry.trim(); // On enlève le retour à la ligne

    // Si la commande demande d'ouvrir le portail
    if (motDuRasberry == "ouvrir" && !ouvertureEnCours && !portailOuvert) 
      return true;

    // Si la commande demande de fermer le portail
    else if (motDuRasberry == "fermer" && !fermetureEnCours && !portailFermer)
      return true;
    
  }
  return false;
}