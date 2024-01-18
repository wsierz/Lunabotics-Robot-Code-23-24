#include <Servo.h>

Servo test;

void setup() {
  Serial.begin(115200);
  test.attach(13);
}

int speed;

void loop() {
  if (Serial.available())
  {
    speed = Serial.parseInt();
    test.writeMicroseconds(speed);
  }

  Serial.write(test.readMicroseconds());

}
