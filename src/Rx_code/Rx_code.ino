#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 10); // CE, CSN
const byte address[6] = "00001";

#define ENA 3
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENB 9

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, 225); // motor speed (0-255)
  analogWrite(ENB, 225);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char command;
    radio.read(&command, sizeof(command));
    Serial.println(command);

    switch (command) {
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        stopMotors();
        break;
    }
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
