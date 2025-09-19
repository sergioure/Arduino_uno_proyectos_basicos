// Proyecto: Luces nocturnas automáticas secuenciales
// Arduino Uno + 6 LEDs + Módulo LDR (4 pines)

const int leds[6] = {2, 3, 4, 5, 6, 7};  // Pines de los LEDs
const int ldrDigital = A0;               // Pin D0 del módulo LDR (conectado a A0 del Arduino)

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
  pinMode(ldrDigital, INPUT); // Lectura digital del sensor LDR
}

void loop() {
  int estadoLuz = digitalRead(ldrDigital);

  if (estadoLuz == HIGH) {
    // 🌙 Noche → Encender secuencialmente
    for (int i = 0; i < 6; i++) {
      digitalWrite(leds[i], HIGH);
      delay(200);
    }
  } else {
    // ☀️ Día → Apagar secuencialmente
    for (int i = 0; i < 6; i++) {
      digitalWrite(leds[i], LOW);
      delay(200);
    }
  }
}