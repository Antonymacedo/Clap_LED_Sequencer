#define SOUND_SENSOR_PIN 2
const int LED_PINS[4] = {3, 4, 5, 6};
int clapCount = 0;
unsigned long lastClapTime = 0;
const int clapDelay = 300;  // Tempo para ignorar ruídos

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
  pinMode(SOUND_SENSOR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  int soundValue = digitalRead(SOUND_SENSOR_PIN);

  if (soundValue == HIGH) {
    unsigned long currentTime = millis();

    // Verifica o tempo entre claps para ignorar ruídos
    if (currentTime - lastClapTime > clapDelay) {
      clapCount++;
      if (clapCount > 5) clapCount = 1; // Reinicia após a quinta palma

      updateLeds();
      Serial.print("Clap Count: ");
      Serial.println(clapCount);
      delay(500); // Ignora múltiplos sinais de uma só palma
    }

    lastClapTime = currentTime;
  }
}

void updateLeds() {
  if (clapCount < 5) {
    // Acende LEDs de forma sequencial
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED_PINS[i], i < clapCount ? HIGH : LOW);
    }
  } else {
    // Na quinta palma, pisca todos os LEDs
    for (int i = 0; i < 3; i++) {  // Pisca três vezes
      setAllLeds(HIGH);
      delay(200);
      setAllLeds(LOW);
      delay(200);
    }
  }
}

void setAllLeds(bool state) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED_PINS[i], state);
  }
}