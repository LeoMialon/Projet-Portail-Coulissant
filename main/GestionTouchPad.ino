


// Si un nombre est taper, l'avoir
int SetNumberPad() {
  uint8_t data = KeyPad.read();
  switch (data) {
    case 0xE1:
      return 1;
    case 0xE2:
      return 2;
    case 0xE3:
      return 3;
    case 0xE4:
      return 4;
    case 0xE5:
      return 5;
    case 0xE6:
      return 6;
    case 0xE7:
      return 7;
    case 0xE8:
      return 8;
    case 0xE9:
      return 9;
    case 0xEB :
      return 0;
    case 0xEA :
      return 10;
    case 0xEC :
      return 11;
    default:
      return -1;
  }
}

// Retourne vrai quand l'utilisateur utilise le TouchPad
bool KeypadUse()
{
  if(KeyPadNumber == 10) // Si la touche "*" est taper
    wantHelp++;
  
  return KeyPadNumber >= 0 && KeyPadNumber < 10; // Entre 0 et 9
}