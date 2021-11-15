#include <LiquidCrystal_I2C.h>
#include <OneButton.h>
#include "tones.h"

#define LCD_I2C_ADDR 0x27
#define BTNPIN 8
#define BUZZER 9
#define POTPIN A0
#define US_TRIG 13
#define US_ECHO 12

LiquidCrystal_I2C lcd(LCD_I2C_ADDR, 16, 2);
OneButton btn(BTNPIN, false);

const char pauseicon[] = {0x00, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x00};
const char resumeicon[] = {0x00, 0x08, 0x0C, 0x0E, 0x0E, 0x0C, 0x08, 0x00};

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, pauseicon);
  lcd.createChar(1, resumeicon);
  lcd.setCursor(2, 0);
  lcd.print("Tomato Clock");
  lcd.setCursor(1, 1);
  lcd.print("By yangshunhuai");
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(4, 0);
  lcd.print("Working");
  lcd.setCursor(15, 0);
  lcd.write(byte(0));
}
