#include <U8g2lib.h>
#include <OneButton.h>
#include "tones.h"

#define BTNLEFT 2
#define BTNENTER 3
#define BTNRIGHT 4
#define BUZZER 10
#define US_TRIG 6
#define US_ECHO 7

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
OneButton btn(BTNPIN, false);

const char pauseicon[] = {0x00, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x00};
const char resumeicon[] = {0x00, 0x08, 0x0C, 0x0E, 0x0E, 0x0C, 0x08, 0x00};

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}
