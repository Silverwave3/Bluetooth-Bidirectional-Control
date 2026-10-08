#include <SoftwareSerial.h>

const int buttonPin = 2;
const int motorPWMPin = 9;
SoftwareSerial BTSerial(10, 11); // RX, TX
int motorSpeed = 0;

bool lastButtonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(motorPWMPin, OUTPUT);
  
  Serial.begin(9600);
  BTSerial.begin(9600); // 根據你的 HC-05 正常通訊鮑率設定 (通常為 9600 或 38400)
}

void loop() {
  // 1. 讀取按鈕狀態並傳送指令控制 B 的 LED
  bool currentButtonState = digitalRead(buttonPin);
  if (currentButtonState != lastButtonState) {
    delay(50); // 簡易去彈跳 (Debounce)
    if (currentButtonState == LOW) { // 按下按鈕
      BTSerial.println("B:1"); 
      Serial.println("傳送: 1 (開燈)");
      //BTSerial.println("Turn on the LED");
    } else { // 放開按鈕
      BTSerial.println("B:0"); 
      Serial.println("傳送: 0 (關燈)");
    }
    lastButtonState = currentButtonState;
  }

  if (BTSerial.available()) {
    String command = BTSerial.readStringUntil('\n');
    command.trim();

    Serial.print("Received: ");
    Serial.println(command);
    
    if (command.startsWith("P:")) {

      // 把 "P:128" 的 "P:" 去掉，只留下 "128"
      motorSpeed = command.substring(2).toInt();

      // 保證數值只在 PWM 合法範圍
      motorSpeed = constrain(motorSpeed, 0, 255);

     // 輸出 PWM 給馬達驅動電路
      analogWrite(motorPWMPin, motorSpeed);

      Serial.print("Motor PWM: ");
      Serial.println(motorSpeed);
    }
  }
}
