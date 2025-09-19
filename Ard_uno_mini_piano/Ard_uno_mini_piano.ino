// Mini piano de 8 notas con Arduino Uno


int buzzer = 8;
int botones[] = {2, 3, 4, 5, 6, 7, 9, 10}; // 8 botones
int notas[] = {262, 294, 330, 349, 392, 440, 494, 523}; 
// DO, RE, MI, FA, SOL, LA, SI, DO

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(botones[i], INPUT_PULLUP); // Botones con pull-up
  }
  pinMode(buzzer, OUTPUT);
}

void loop() {
  bool tocando = false;
  for (int i = 0; i < 8; i++) {
    if (digitalRead(botones[i]) == LOW) { // Si se presiona el botón
      tone(buzzer, notas[i]);
      tocando = true;
    }
  }
  if (!tocando) {
    noTone(buzzer); // Silencio si no se aprieta nada
  }
}
