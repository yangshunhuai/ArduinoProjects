#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define resistorPin A0
#define touchPin 2
#define buzzerPin 4
#define ledPin 7

LiquidCrystal_I2C scr(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  scr.init();
  scr.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  firstStart();
  delay(1000);
  scr.setCursor(0, 1);
  scr.print("   ^");
  while (digitalRead(2) == LOW) {
    int decValue = getResistorValue();
    printDecValue(decValue);
  }
  int decValue1 = getResistorValue();
  String hour = String(decValue1);
  assignFirst(decValue1);
  delay(1000);

  scr.setCursor(0, 1);
  scr.print("    ^");
  while (digitalRead(2) == LOW) {
    int decValue = getResistorValue();
    printDecValue(decValue);
  }
  int decValue2 = getResistorValue();
  String decValue2AsString = String(decValue2);
  hour.concat(decValue2AsString);
  assignSecond(decValue2);
  delay(1000);

  scr.setCursor(0, 1);
  scr.print("           ^");
  while (digitalRead(2) == LOW) {
    int decValue = getResistorValue();
    printDecValue(decValue);
  }
  int decValue3 = getResistorValue();
  String minute = String(decValue3);
  assignThird(decValue3);
  delay(1000);

  scr.setCursor(0, 1);
  scr.print("            ^");
  while (digitalRead(2) == LOW) {
    int decValue = getResistorValue();
    printDecValue(decValue);
  }
  int decValue4 = getResistorValue();
  String decValue4AsString = String(decValue4);
  minute.concat(decValue4AsString);
  assignFourth(decValue4);
  delay(1000);

  int hourInt = hour.toInt();
  int minuteInt = minute.toInt();
  startTimer(hourInt, minuteInt);
}

int getResistorValue(void) {
  int resistorVal = analogRead(resistorPin);
  int decValue = resistorVal / 103;
  return decValue;
}

void firstStart() {
  scr.clear();
  scr.setCursor(0, 0);
  scr.print("Hr 00  Min 00  ");
}

void printDecValue(int value) {
  scr.setCursor(15, 0);
  scr.print(value);
}

void assignFirst(int value) {
  scr.setCursor(3, 0);
  scr.print(value);
}

void assignSecond(int value) {
  scr.setCursor(4, 0);
  scr.print(value);
}

void assignThird(int value) {
  scr.setCursor(11, 0);
  scr.print(value);
}

void assignFourth(int value) {
  scr.setCursor(12, 0);
  scr.print(value);
}

void displayHourTime(int hour, int minute) {
  scr.setCursor(14, 0);
  scr.print(hour);
  scr.setCursor(14, 1);
  scr.print(minute);
}

void startTimer(int hour, int minute) {
  scr.clear();
  scr.setCursor(5, 0);
  scr.print("START");
  scr.setCursor(5, 1);
  scr.print("TIMING");
  delay(1000);

  for (int i = 3; i > 0; i--) {
    scr.clear();
    scr.setCursor(7, 0);
    scr.print(i);
    delay(1000);
  }

  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);
  scr.clear();
  scr.setCursor(7, 0);
  scr.print("GO");
  delay(1000);
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);

  scr.clear();
  scr.setCursor(0, 0);
  scr.print("  Hours Left: ");
  scr.setCursor(0, 1);
  scr.print("Minutes Left: ");
  displayHourTime(hour, minute);

  int sum;
  Serial.println(hour);
  Serial.println(minute);
  while (not(hour != 0 && minute != 0)) {
    delay(60000);
    minute -= 1;
    sum += 1;
    if (sum == 60) {
      hour -= 1;
      sum = 0;
    }
    if (hour == 0 && minute == 0) {
      break;
    }
    displayHourTime(hour, minute);
  }
  scr.clear();
  scr.setCursor(3, 0);
  scr.print("TIME'S UP!");
  digitalWrite(4, HIGH);
  while (not(digitalRead(2) == HIGH)) {
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
    delay(1000);
  }
  digitalWrite(4, LOW);
}
