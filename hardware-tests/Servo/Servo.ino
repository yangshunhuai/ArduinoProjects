#include <Servo.h>
Servo servoA;
Servo servoB;
void setup() {
  // put your setup code here, to run once:
  servoA.attach(3);
  servoB.attach(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  servoA.write(90);
  servoB.write(90);
  delay(1000);
  servoA.write(0);
  servoB.write(0);
  delay(1000);
}
