String valueRasberry = "";  // Valeur de ce arrive du RasberryPi / Site Web

// Lire ce qui arrive du RasberryPi
String ReadRasberryPi() {

  // On vérifie si une donnée est envoyé
  if (Serial.available() > 0) {
    valueRasberry = Serial.readString();  // On lit le mot envoyé par le RasberryPi
    valueRasberry.trim();                 // On enlève le retour à la ligne
  }

  else valueRasberry = "";

  return valueRasberry;
}


// Voir s'il y a une donnée envoyé par le rasberryPi et réagir en conséquence
bool CheckRasberryPi() {
  String value = ReadRasberryPi();

  // Si le Rasberry envoit une donnée
  if (value != "") {
    Println(value);

    // Si la commande demande d'ouvrir le portail
    if (value == "ouvrir" && !ouvertureEnCours) {
      ouvertureEnCours = true;
      fermetureEnCours = false;
      return true;
    }

    // Si la commande demande de fermer le portail
    else if (value == "fermer" && !fermetureEnCours) {
      ouvertureEnCours = false;
      fermetureEnCours = true;
      return true;
    }
  }
  return false;
}