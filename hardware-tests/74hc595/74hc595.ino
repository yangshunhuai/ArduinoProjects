#define dat 2
#define clk 4
#define lck 5

void setup() {
  // put your setup code here, to run once:
  pinMode(dat, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(lck, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  out(128);
  delay(1000);
  out(64);
  delay(1000);
  out(32);
  delay(1000);
  out(16);
  delay(1000);
  out(8);
  delay(1000);
  out(4);
  delay(1000);
  out(2);
  delay(1000);
  out(1);
  delay(1000);
}

void out(int data) {
  digitalWrite(lck, LOW);
  shiftOut(dat, clk, MSBFIRST, data);
  digitalWrite(lck, HIGH);
}
