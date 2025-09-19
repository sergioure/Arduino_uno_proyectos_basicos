// Definición de pines para los LEDs
const int LED_TOP_LEFT = 7;
const int LED_TOP_CENTER = 8;
const int LED_TOP_RIGHT = 9;
const int LED_CENTER = 10;
const int LED_BOTTOM_LEFT = 11;
const int LED_BOTTOM_CENTER = 12;
const int LED_BOTTOM_RIGHT = 13;

// Pin del botón y buzzer
const int BUTTON_PIN = A0;
const int BUZZER_PIN = A1;

// Variables para el control del botón
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Variables para la animación
bool rolling = false;
unsigned long rollStartTime = 0;
unsigned long currentDelay = 80; // Velocidad inicial más rápida
int currentFace = 1;

void setup() {
  // Configurar pines de LEDs como salida
  pinMode(LED_TOP_LEFT, OUTPUT);
  pinMode(LED_TOP_CENTER, OUTPUT);
  pinMode(LED_TOP_RIGHT, OUTPUT);
  pinMode(LED_CENTER, OUTPUT);
  pinMode(LED_BOTTOM_LEFT, OUTPUT);
  pinMode(LED_BOTTOM_CENTER, OUTPUT);
  pinMode(LED_BOTTOM_RIGHT, OUTPUT);
  
  // Configurar pin del botón como entrada y buzzer como salida
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Apagar todos los LEDs inicialmente
  clearAllLEDs();
  
  // Iniciar comunicación serial para debugging (opcional)
  Serial.begin(9600);
  
  // Semilla aleatoria basada en una entrada analógica flotante
  randomSeed(analogRead(A2));
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  
  // Detectar flanco de subida del botón con debounce
  if (buttonState == HIGH && lastButtonState == LOW && 
      millis() - lastDebounceTime > debounceDelay) {
    
    lastDebounceTime = millis();
    
    if (!rolling) {
      // Iniciar animación de lanzamiento
      rolling = true;
      rollStartTime = millis();
      currentDelay = 80; // Velocidad inicial más rápida
      Serial.println("Iniciando lanzamiento...");
    }
  }
  
  lastButtonState = buttonState;
  
  if (rolling) {
    // Animación de lanzamiento en curso
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - rollStartTime;
    
    // Generar sonido con el buzzer (tono que varía con la velocidad)
    int toneFreq = map(constrain(currentDelay, 80, 500), 80, 500, 800, 300);
    tone(BUZZER_PIN, toneFreq, 50);
    
    // Mostrar cara aleatoria
    showRandomFace();
    
    // Reducir gradualmente la velocidad (animación de 3 segundos)
    if (elapsedTime > 2000) {
      // Último segundo: reducir velocidad más rápido
      currentDelay = map(elapsedTime, 2000, 3000, 200, 500);
    } else if (elapsedTime > 1000) {
      // Segundo intermedio: transición de velocidad
      currentDelay = map(elapsedTime, 1000, 2000, 100, 200);
    }
    
    // Detener la animación después de 3 segundos
    if (elapsedTime > 3000) {
      rolling = false;
      noTone(BUZZER_PIN); // Detener sonido
      
      // Sonido de resultado
      tone(BUZZER_PIN, 600, 200);
      
      // Mostrar cara final aleatoria
      currentFace = random(1, 7);
      showFace(currentFace);
      Serial.print("Cara final: ");
      Serial.println(currentFace);
    }
    
    delay(currentDelay);
  }
}

void showRandomFace() {
  int randomFace = random(1, 7);
  showFace(randomFace);
}

void showFace(int face) {
  // Apagar todos los LEDs primero
  clearAllLEDs();
  
  // Encender LEDs según la cara del dado
  switch(face) {
    case 1:
      digitalWrite(LED_CENTER, HIGH);
      break;
      
    case 2:
      digitalWrite(LED_TOP_LEFT, HIGH);
      digitalWrite(LED_BOTTOM_RIGHT, HIGH);
      break;
      
    case 3:
      digitalWrite(LED_TOP_LEFT, HIGH);
      digitalWrite(LED_CENTER, HIGH);
      digitalWrite(LED_BOTTOM_RIGHT, HIGH);
      break;
      
    case 4:
      digitalWrite(LED_TOP_LEFT, HIGH);
      digitalWrite(LED_TOP_RIGHT, HIGH);
      digitalWrite(LED_BOTTOM_LEFT, HIGH);
      digitalWrite(LED_BOTTOM_RIGHT, HIGH);
      break;
      
    case 5:
      digitalWrite(LED_TOP_LEFT, HIGH);
      digitalWrite(LED_TOP_RIGHT, HIGH);
      digitalWrite(LED_CENTER, HIGH);
      digitalWrite(LED_BOTTOM_LEFT, HIGH);
      digitalWrite(LED_BOTTOM_RIGHT, HIGH);
      break;
      
    case 6:
      digitalWrite(LED_TOP_LEFT, HIGH);
      digitalWrite(LED_TOP_CENTER, HIGH);
      digitalWrite(LED_TOP_RIGHT, HIGH);
      digitalWrite(LED_BOTTOM_LEFT, HIGH);
      digitalWrite(LED_BOTTOM_CENTER, HIGH);
      digitalWrite(LED_BOTTOM_RIGHT, HIGH);
      break;
  }
}

void clearAllLEDs() {
  digitalWrite(LED_TOP_LEFT, LOW);
  digitalWrite(LED_TOP_CENTER, LOW);
  digitalWrite(LED_TOP_RIGHT, LOW);
  digitalWrite(LED_CENTER, LOW);
  digitalWrite(LED_BOTTOM_LEFT, LOW);
  digitalWrite(LED_BOTTOM_CENTER, LOW);
  digitalWrite(LED_BOTTOM_RIGHT, LOW);
}