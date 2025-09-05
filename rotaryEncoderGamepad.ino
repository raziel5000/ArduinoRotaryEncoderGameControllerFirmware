#define CLK_PIN 2
#define DT_PIN 3
#define SW_PIN 4
#define BTTN_PIN 5

int position = 0;
int lastClk = HIGH;
bool taster = LOW;
bool last_taster = LOW;
int lastButtonState = LOW;

void setup() {
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(BTTN_PIN, INPUT);
  Serial.begin(19200);  // oppure 115200 per maggiore velocità
}

void loop() {
  // Rotary Encoder
  int currentClk = digitalRead(CLK_PIN);
  if (lastClk == HIGH && currentClk == LOW) {
    int dtValue = digitalRead(DT_PIN);
    if (dtValue == HIGH) {
      position++;
    } else {
      position--;
    }
  }
  lastClk = currentClk;

  // Pulsante sull'encoder (SW_PIN)
  taster = !digitalRead(SW_PIN);  // logica invertita per via di INPUT_PULLUP
  if (taster != last_taster) {
    last_taster = taster;
  }

  // Pulsante esterno (BTTN_PIN) 
  int buttonState = digitalRead(BTTN_PIN);

  // Pacchetto: header, LSB, MSB, button1, button2, checksum
  uint8_t packet[6];
  packet[0] = 0xAA;  // header
  packet[1] = position & 0xFF;          // LSB
  packet[2] = (position >> 8) & 0xFF;   // MSB
  packet[3] = (uint8_t)buttonState;     // Pulsante esterno
  packet[4] = (uint8_t)taster;          // Pulsante sull'encoder

  // Calcolo checksum su LSB, MSB, button1, button2
  packet[5] = (packet[1] + packet[2] + packet[3] + packet[4]) & 0xFF;

  Serial.write(packet, 6);  // invia l'intero pacchetto

  delay(1);
}
