String valueRasberry = ""; // Valeur de ce arrive du RasberryPi / Site Web
String test = "TEST";

// Lire ce qui arrive du RasberryPi
String ReadRasberryPi() {
  char read;

  // On vérifie si une donnée est envoyé pour rénitialiser la valeur s'il n'y en a pas  
  if(!Serial.available())
    valueRasberry = "";

  // On entre dans la boucle si une donnée est envoyé
  while(Serial.available()){
    read = Serial.read();
    if(read != 10)
      valueRasberry += read;
  }

  return valueRasberry;
}


// Voir s'il y a une donnée envoyé par le rasberryPi et réagir en conséquence
bool CheckRasberryPi() {
  String value = ReadRasberryPi();

  // Si le Rasberry envoit une donnée
  if (value != "") {
    Serial.println(value);
    Serial.println(" ");

    // Si la commande demande d'ouvrir le portail
    if (value == "ouvrir" && !ouvertureEnCours) {
      ouvertureEnCours = true;
      fermetureEnCours = false;
      return true;
    }

    // Si la commande demande de fermer le portail
    else if (value == "fermer" && !fermetureEnCours) {
      ouvertureEnCours = true;
      fermetureEnCours = false;
      return true;
    }
  }

  return false;
}