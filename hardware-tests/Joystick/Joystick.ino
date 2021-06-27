void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Current X: ");
  Serial.println(analogRead(A0));
  Serial.print("Current Y: ");
  Serial.println(analogRead(A1));
  Serial.print("Current Switch: ");
  Serial.println(digitalRead(2));
  Serial.println();
  delay(1000);
}
