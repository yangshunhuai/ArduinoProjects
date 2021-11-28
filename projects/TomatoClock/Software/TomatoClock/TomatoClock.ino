/*
 * TomatoClock Main Program
 * Wiring: See hardware schematics
 * Author: yangshunhuai
 * Revision: 1.0
 */

#include <U8g2lib.h>
#include <OneButton.h>
#include <SoftwareSerial.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include "tones.h"

// Device pins
#define BTNLEFT    2
#define BTNENTER   3
#define BTNRIGHT   4
#define BUZZER     10
#define US_TRIG    5
#define US_ECHO    6
#define BT_SER_TX  7
#define BT_SER_RX  8
#define DS1302_CLK A0
#define DS1302_DAT A1
#define DS1302_RST A2
String BT_NAME =   "TomatoClock";

// Devices
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
OneButton btnleft(BTNLEFT, false);
OneButton btnenter(BTNENTER, false);
OneButton btnright(BTNRIGHT, false);
ThreeWire mywire(DS1302_DAT, DS1302_CLK, DS1302_RST);
RtcDS1302<ThreeWire> rtc(mywire);
SoftwareSerial btser(BT_SER_TX, BT_SER_RX);

void setup() {
  // Configure pins
  pinMode(BUZZER, OUTPUT);
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);
  // Configure devices
  u8g2.begin();
  rtc.Begin();
  btser.begin(9600);
  btser.print("AT+NAME" + BT_NAME + "\r\n");
}

void loop() {
  // put your main code here, to run repeatedly:
}
