#include <Servo.h>

const int BUFFER_SIZE = 1;
char buf[BUFFER_SIZE];

Servo test;

void setup() {
  Serial.begin(115200);
  test.attach(5);
}

int speed;

void loop() {
  if (Serial.available())
  {
    Serial.readBytes(buf, BUFFER_SIZE);
    speed = map(buf[0], 0, 256, 1000, 2000);
    test.writeMicroseconds(speed);
  }
}