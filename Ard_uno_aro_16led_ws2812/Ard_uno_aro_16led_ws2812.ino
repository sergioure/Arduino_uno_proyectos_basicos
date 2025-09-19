#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL 6     // Pin de datos del aro WS2812
#define NUMPIXELS 16       // Cantidad de LEDs del aro

// Pines de los 4 botones
#define BOTON1 2
#define BOTON2 3
#define BOTON3 4
#define BOTON4 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

int brillo = 80;  // Brillo de los LEDs (0-255)

void setup() {
  pixels.begin();
  pixels.setBrightness(brillo);
  pixels.show();  // Apagar todos al inicio

  pinMode(BOTON1, INPUT_PULLUP);
  pinMode(BOTON2, INPUT_PULLUP);
  pinMode(BOTON3, INPUT_PULLUP);
  pinMode(BOTON4, INPUT_PULLUP);
}

void loop() {
  bool b1 = !digitalRead(BOTON1);
  bool b2 = !digitalRead(BOTON2);
  bool b3 = !digitalRead(BOTON3);
  bool b4 = !digitalRead(BOTON4);

  // --- Colores individuales ---
  if (b1 && !b2 && !b3 && !b4) {
    setColor(255, 0, 0); // 🔴 Rojo
  } 
  else if (b2 && !b1 && !b3 && !b4) {
    setColor(0, 255, 0); // 🟢 Verde
  } 
  else if (b3 && !b1 && !b2 && !b4) {
    setColor(0, 0, 255); // 🔵 Azul
  }

  // --- Combinaciones de botones ---
  else if (b1 && b2) {
    setColor(255, 255, 0); // Rojo + Verde = Amarillo
  } 
  else if (b1 && b3) {
    setColor(255, 0, 255); // Rojo + Azul = Magenta
  } 
  else if (b2 && b3) {
    setColor(0, 255, 255); // Verde + Azul = Cian
  }

  // --- Secuencias aleatorias ---
  else if (b4) {
    randomSequence();
  }
}

// Función para encender todo el aro con un color
void setColor(int r, int g, int b) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}

// Función para secuencias aleatorias
void randomSequence() {
  int opcion = random(1, 4); // 1 a 3
  if (opcion == 1) {
    // Secuencia 1: giro
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.clear();
      pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // 🔵 Azul
      pixels.show();
      delay(100);
    }
  } else if (opcion == 2) {
    // Secuencia 2: todos parpadean
    setColor(255, 0, 255); delay(200);
    setColor(0, 0, 0); delay(200);
  } else if (opcion == 3) {
    // Secuencia 3: arcoíris
    rainbow(20);
  }
}

// Efecto arcoíris
void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < pixels.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show();
    delay(wait);
  }
}
