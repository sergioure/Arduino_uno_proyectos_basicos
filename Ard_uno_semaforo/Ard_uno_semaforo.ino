// Pines para los LEDs
const int LED_ROJO = 7;
const int LED_AMARILLO = 8;
const int LED_VERDE = 9;

void setup() {
  // Configuramos los pines como salida
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
}

void loop() {
  // Encender luz roja
  digitalWrite(LED_ROJO, HIGH);
  delay(3000); // espera 3 segundos
  digitalWrite(LED_ROJO, LOW);

  // Encender luz verde
  digitalWrite(LED_VERDE, HIGH);
  delay(3000); // espera 3 segundos
  digitalWrite(LED_VERDE, LOW);

  // Encender luz amarilla
  digitalWrite(LED_AMARILLO, HIGH);
  delay(1000); // espera 1 segundo
  digitalWrite(LED_AMARILLO, LOW);
}
