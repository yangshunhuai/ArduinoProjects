#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C scr(0x27, 16, 2);

int percentCPU = 0;
int percentMem = 0;
int blockCPU = 0;
int blockMem = 0;
int remainedLinesCPU = 0;
int remainedLinesMem = 0;
String serialData;
char serialCharacter;
byte block1[8] = {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
byte block2[8] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
byte block3[8] = {0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C};
byte block4[8] = {0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E};
byte block5[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  scr.init();
  scr.backlight();
  scr.createChar(0, block1);
  scr.createChar(1, block2);
  scr.createChar(2, block3);
  scr.createChar(3, block4);
  scr.createChar(4, block5);
  printBasic();
}

void loop() {
  // put your main code here, to run repeatedly:
  bool completeSerial = false;
  serialData = "";
  //printBasic();
  while (!completeSerial) {
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();
      // add it to the inputString:
      serialData += inChar;
      // if the incoming character is a newline, set a flag so the main loop can
      // do something about it:
      if (inChar == '\n') {
        completeSerial = true;
        break;
      }
    }
  }
  splitStringAndToInt(serialData, ",");
  printPercentCPU(percentCPU);
  printPercentMem(percentMem);
  processBlockCPU(percentCPU);
  processBlockMem(percentMem);
  int charNumCPU = getCharNum(remainedLinesCPU);
  int charNumMem = getCharNum(remainedLinesMem);
  Serial.print("charNumCPU: ");
  Serial.println(charNumCPU);
  Serial.print("charNumMem: ");
  Serial.println(charNumMem);
  printBlock(blockCPU, charNumCPU, 0);
  printBlock(blockMem, charNumMem, 1);
}

void splitStringAndToInt(String inString, String separator) {
  int commaIndex = inString.indexOf(separator);
  //  Serial.print(commaIndex);
  String str1 = inString.substring(0, commaIndex);
  String str2 = inString.substring(commaIndex + 1);
    Serial.print("str1:");
    Serial.println(str1);
    Serial.print("str2:");
    Serial.println(str2);
  percentCPU = str1.toInt();
  percentMem = str2.toInt();
}

void printBlock(int blockPartial, int charNumPartial, int row) {
  resetBar(row);
  scr.setCursor(1, row);
  int i = 0;
  for (i; i < blockPartial; i++) {
    scr.write(byte(4));
  }
  if (charNumPartial != -1) {
    scr.write(byte(charNumPartial));
  }
}

void processBlockCPU(int percentCPUPartial) {
  int totalLines = percentCPUPartial / 2;
  blockCPU = totalLines / 5;
//  Serial.print("totalLines: ");
//  Serial.println(totalLines);
  int blockCPUx5 = blockCPU * 5;
  remainedLinesCPU = totalLines - blockCPUx5;
}

void processBlockMem(int percentMemPartial) {
  int totalLines = percentMemPartial / 2;
  blockMem = totalLines / 5;
  int blockMemx5 = blockMem * 5;
//  Serial.print("totalLines: ");
//  Serial.println(totalLines);
  remainedLinesMem = totalLines - blockMemx5;
}

int getCharNum(int lines) {
  int charNum = lines - 1;
  return charNum;
}

void printPercentCPU(int percentCPUPartial) {
  resetPercent(0);
  String percentCPUString = String(percentCPUPartial);
  int digits = percentCPUString.length();
  switch (digits) {
    case 1 :
      scr.setCursor(14, 0);
      break;
    case 2 :
      scr.setCursor(13, 0);
      break;
    case 3 :
      scr.setCursor(12, 0);
      break;
  }
  scr.print(percentCPUPartial);
}

void printPercentMem(int percentMemPartial) {
  resetPercent(1);
  String percentMemString = String(percentMemPartial);
  int digits = percentMemString.length();
  switch (digits) {
    case 1 :
      scr.setCursor(14, 1);
      break;
    case 2 :
      scr.setCursor(13, 1);
      break;
    case 3 :
      scr.setCursor(12, 1);
      break;
  }
  scr.print(percentMemPartial);
}

void printBasic() {
  scr.clear();
  scr.setCursor(0, 0);
  scr.print("[");
  scr.setCursor(11, 0);
  scr.print("]");
  scr.setCursor(15, 0);
  scr.print("%");
  scr.setCursor(0, 1);
  scr.print("[");
  scr.setCursor(11, 1);
  scr.print("]");
  scr.setCursor(15, 1);
  scr.print("%");
}

void resetBar(int row) {
  scr.setCursor(1, row);
  scr.print("          ");
}

void resetPercent(int row) {
  scr.setCursor(12, row);
  scr.print("   ");
}
