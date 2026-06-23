#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <MPU6050.h>

MPU6050 mpu;
RF24 radio(8, 10); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  char command = 'S';  // Default to Stop

  if (ay > 10000)      command = 'B';  // Tilt Forward
  else if (ay < -10000) command = 'F'; // Tilt Backward
  else if (ax > 10000)  command = 'R'; // Tilt Left
  else if (ax < -10000) command = 'L'; // Tilt Right
  else                  command = 'S'; // Stop

  radio.write(&command, sizeof(command));
  delay(100); // 10 times per second
}

