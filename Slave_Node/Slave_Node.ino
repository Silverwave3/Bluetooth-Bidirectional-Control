#include <SoftwareSerial.h>

const int LED_PIN = 7;
const int POT_PIN = A0;

SoftwareSerial BT(10, 11);  // RX, TX

int lastPotValue = -1;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);
  BT.begin(9600);

  Serial.println("Slave ready");
}

void loop() {

  // 1. Receive button command from Master
  if (BT.available()) {
    String command = BT.readStringUntil('\n');
    command.trim();

    Serial.print("Received: ");
    Serial.println(command);

    if (command == "B:1") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
    }
    else if (command == "B:0") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
    }
  }

  // 2. Read potentiometer
  int rawPotValue = analogRead(POT_PIN);

  // ADC 0~1023 -> PWM 0~255
  int potValue = map(rawPotValue, 0, 1023, 0, 255);

  // 3. Send potentiometer value to Master
  if (abs(potValue - lastPotValue) >= 2) {

    BT.print("P:");
    BT.println(potValue);

    Serial.print("Sent: P:");
    Serial.println(potValue);

    lastPotValue = potValue;
  }

  delay(50);
}