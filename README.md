# Clap LED Sequencer👋
![Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?style=flat-square&logo=arduino&logoColor=white)
![Language](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)

 
Este projeto controla uma sequência de LEDs acesos por palmas.  
Funcionalidades:

| Ação| LED |
|---|---|
| 1 palma:  | 🟡 Amarelo|
| 2 palmas: | 🔵 Azul |
| 3 palmas: | 🟢 Verde  |
| 4 palmas: | 🔴 Vermelho |
| 5 palmas: | todos os LEDs piscam 3 vezes |



## Materiais⚙️
- Arduino Uno

- 4 LEDs

- 4 resistores de 220 ohms

- Sensor de som digital (KY-038)

![image](https://github.com/user-attachments/assets/3e8872e1-dc04-4727-bd0c-6295504bf7a9)

(Pinagem do Sensor de Som)

- Fios e protoboard

## Como Usar🤖
1. Carregue o código `clap_led_sequencer.ino` no Arduino usando o Arduino IDE.  
2. Monte o circuito conforme o esquema `wiring_diagram.png`.  
3. Experimente acender LEDs com palmas!

## Conexões
| Componente | Pino do Arduino |
|------------|-----------------|
| LED1       | D3              |
| LED2       | D4              |
| LED3       | D5              |
| LED4       | D6              |
| Sensor OUT | D2              |
| Sensor VCC | 5V              |
| Sensor GND | GND             |

## Montagem🛠️
1. Conecte os LEDs ao protoboard e ligue os cátodos ao GND com resistores de 220 ohms.
2. Os anódos dos LEDs devem ser conectados aos pinos digitais do Arduino (D3 a D6).
3. Conecte o sensor de som:  
   - OUT no pino D2 do Arduino.  
   - VCC ao pino 5V e GND ao GND.
4. Verifique as conexões antes de alimentar o Arduino.

## Código💻

```
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
```

## Resultado❗

![90872eda-3357-4bd7-a766-d153e9d73cda](https://github.com/user-attachments/assets/976ff309-b5bb-4fd1-a78a-a7ccdc15ec66)

Foto do resultado final



https://github.com/user-attachments/assets/ab7af1bd-b32c-471d-9ab0-2a387c27bdd4

Vidéo do resultado final
