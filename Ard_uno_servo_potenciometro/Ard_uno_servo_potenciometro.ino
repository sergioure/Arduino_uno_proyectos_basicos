// Proyecto: Control de servomotor con potenciómetro
// Arduino Uno + Servo + Potenciómetro

#include <Servo.h>

Servo miServo;             // Creamos un objeto servo
const int pinServo = 9;    // Pin de control del servomotor
const int pinPot = A0;     // Pin del potenciómetro (entrada analógica)

void setup() {
  miServo.attach(pinServo); // Conectamos el servo al pin 9
}

void loop() {
  int valorPot = analogRead(pinPot);             // Leemos el potenciómetro (0 a 1023)
  int angulo = map(valorPot, 0, 1023, 0, 180);   // Convertimos a ángulo (0° a 180°)
  miServo.write(angulo);                         // Movemos el servo
  delay(15);                                     // Pequeña pausa para estabilidad
}
