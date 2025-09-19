// Juego "Atrapa la luz" con 7 LEDs - Arduino Uno
// Con aumento de velocidad al acertar

const int numLeds = 7;
int leds[numLeds] = {2, 3, 4, 5, 6, 7, 8};
int boton = 9;
int ledError = 10;
int buzzer = 11;

int posicion = 0;         // LED actual
bool direccion = true;    // true = derecha, false = izquierda

int delayBase = 200;      // Velocidad inicial (ms)
int delayActual = delayBase; 

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(boton, INPUT_PULLUP);
  pinMode(ledError, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Apagar todos los LEDs
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], LOW);
  }

  // Encender el LED actual
  digitalWrite(leds[posicion], HIGH);
  delay(delayActual);

  // Revisar si se presionó el botón
  if (digitalRead(boton) == LOW) {
    if (posicion == numLeds / 2) {  
      // Acierto: aumentar velocidad
      ganar();
      if (delayActual > 50) {       // límite de velocidad
        delayActual -= 20;          // cada acierto = más rápido
      }
    } else {
      // Error → reiniciar velocidad
      perder();
      delayActual = delayBase;
    }
  }

  // Mover la luz
  if (direccion) {
    posicion++;
    if (posicion >= numLeds - 1) direccion = false;
  } else {
    posicion--;
    if (posicion <= 0) direccion = true;
  }
}

void ganar() {
  // Efecto de acierto
  for (int i = 0; i < 2; i++) {
    tone(buzzer, 1000);
    digitalWrite(leds[posicion], LOW);
    delay(100);
    noTone(buzzer);
    digitalWrite(leds[posicion], HIGH);
    delay(100);
  }
}

void perder() {
  // Efecto de error
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledError, HIGH);
    tone(buzzer, 200);
    delay(200);
    digitalWrite(ledError, LOW);
    noTone(buzzer);
    delay(200);
  }
}
