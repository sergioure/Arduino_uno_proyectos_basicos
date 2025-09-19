#include <OneWire.h>
#include <DallasTemperature.h>
#include <TM1637Display.h>

// --- Pines ---
#define ONE_WIRE_BUS 2   // Pin de datos del DS18B20
#define CLK 3            // Pin CLK del TM1637
#define DIO 4            // Pin DIO del TM1637

// --- Objetos ---
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
TM1637Display display(CLK, DIO);

void setup() {
  sensors.begin();
  display.setBrightness(0x0f); // Brillo máximo
}

void loop() {
  sensors.requestTemperatures();
  int tempC = (int)sensors.getTempCByIndex(0); // Leer solo parte entera en °C

  // Mostrar temperatura con "C" al final
  // Ejemplo: 28°C se verá como "28 C"
  uint8_t data[] = {
    display.encodeDigit((tempC / 10) % 10), // Decenas
    display.encodeDigit(tempC % 10),        // Unidades
    0,                                      // Espacio en blanco
    0x39                                    // Segmentos que forman "C"
  };

  display.setSegments(data);

  delay(1000);
}
