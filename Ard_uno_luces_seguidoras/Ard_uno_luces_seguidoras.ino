int leds[] = {2,3,4,5,6,7,8,9,10,11}; // Pines de los 10 LEDs
int numLeds = 10;

void setup() {
  for(int i=0; i<numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // De izquierda a derecha
  for(int i=0; i<numLeds; i++) {
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
  }
  // De derecha a izquierda
  for(int i=numLeds-1; i>=0; i--) {
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
  }
}
