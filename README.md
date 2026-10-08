# Bluetooth-Bidirectional-Control

## Task 4-1

Bidirectional Bluetooth communication using two Arduino Uno boards and HC-05 modules.

### Student A - Master
- Push button
- DC motor with L293D
- HC-05 Master

### Student B - Slave
- Potentiometer
- LED
- HC-05 Slave

## Communication Protocol

- Baud rate: 9600
- Master -> Slave
  - `B:1` = LED ON
  - `B:0` = LED OFF
- Slave -> Master
  - `P:<0-255>` = Motor PWM speed
