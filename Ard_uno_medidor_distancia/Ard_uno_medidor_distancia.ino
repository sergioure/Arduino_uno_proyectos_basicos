// Proyecto: Detector de distancia con sensor ultrasónico y LEDs
// Arduino Uno + HC-SR04 + 6 LEDs
// Autor: Sergio Ureña

const int trigPin = 8;   // Pin TRIG del sensor ultrasónico
const int echoPin = 9;   // Pin ECHO del sensor ultrasónico
const int leds[6] = {2, 3, 4, 5, 6, 7};  // Pines de los 6 LEDs

long duracion;
int distancia;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  for (int i = 0; i < 6; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  Serial.begin(9600); // Para ver la distancia en el monitor serie
}

void loop() {
  // Enviar pulso ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Medir tiempo del eco
  duracion = pulseIn(echoPin, HIGH);
  
  // Calcular distancia en cm
  distancia = duracion * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Control de LEDs
  if (distancia > 30) {
    // Ningún LED encendido
    for (int i = 0; i < 6; i++) {
      digitalWrite(leds[i], LOW);
    }
  } else {
    // Escala de 0 a 30 cm → 6 LEDs
    int numLeds = map(distancia, 100, 5, 0, 6);
    if (numLeds > 6) numLeds = 6;
    if (numLeds < 0) numLeds = 0;

    for (int i = 0; i < 6; i++) {
      if (i < numLeds) {
        digitalWrite(leds[i], HIGH);
      } else {
        digitalWrite(leds[i], LOW);
      }
    }
  }

  delay(100);
}
