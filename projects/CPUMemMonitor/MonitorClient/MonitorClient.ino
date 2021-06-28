#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C scr(0x27, 16, 2);

int percentCPU = 0;
int percentMem = 0;
String serialData;
char serialCharacter;
//bool completeSerial = false;
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
  //  scr.cursor();
  printBasic();
}

void loop() {
  // put your main code here, to run repeatedly:
  //  serialData = readSerial();
  //  Serial.print("Serial Data: ");
  //  Serial.println(serialData);
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
  int blockCPU = translateCPUIntoBlock(percentCPU);
  int blockMem = translateMemIntoBlock(percentMem);
  printPercentCPU(percentCPU);
  printPercentMem(percentMem);
  printBlockMem(blockMem);
  printBlockCPU(blockCPU);
}

void splitStringAndToInt(String inString, String separator) {
  int commaIndex = inString.indexOf(separator);
  //  Serial.print(commaIndex);
  String str1 = inString.substring(0, commaIndex);
  String str2 = inString.substring(commaIndex + 1);
  //  Serial.print("str1:");
  //  Serial.println(str1);
  //  Serial.print("str2:");
  //  Serial.println(str2);
  percentCPU = str1.toInt();
  percentMem = str2.toInt();
}

int translateCPUIntoBlock(int valueCPU) {
  blockCPU = valueCPU / 15;
  return blockCPU;
}

int translateMemIntoBlock(int valueMem) {
  blockMem = valueMem / 15;
  return blockMem;
}

String readSerial() {
  String receivedString;
  char singleChar;
  while (Serial.available()) {
    singleChar = Serial.read();
    if (singleChar != "\n") {
      receivedString += singleChar;
    } else {
      break;
    }
  }
  if (receivedString.length() > 0) {
    //    Serial.print("receivedString:");
    //    return receivedString;
  } else {
    return "nothing";
  }
}

void printBlockCPU(int blockCPU) {
  resetBarCPU();
  scr.setCursor(5, 0);
  int i = 0;
  for (i; i < blockCPU; i++) {
    scr.write(byte(4));
  }
}

void printBlockMem(int blockMem) {
  resetBarMem();
  scr.setCursor(5, 1);
  int j = 0;
  for (j; j < blockMem; j++) {
    scr.write(byte(4));
  }
}

void processBlockCPU(int percentCPUPartial) {
  int blockNum = translateCPUIntoBlock(percentCPUPartial);
  
}

void printPercentCPU(int percentCPUPartial) {
  resetCPUPercent();
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
  resetMemPercent();
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
  scr.print("CPU:[");
  scr.setCursor(11, 0);
  scr.print("]");
  scr.setCursor(15, 0);
  scr.print("%");
  scr.setCursor(0, 1);
  scr.print("Mem:[");
  scr.setCursor(11, 1);
  scr.print("]");
  scr.setCursor(15, 1);
  scr.print("%");
}

void resetBarCPU() {
  scr.setCursor(5, 0);
  scr.print("      ");
}

void resetBarMem() {
  scr.setCursor(5, 1);
  scr.print("      ");
}

void resetCPUPercent() {
  scr.setCursor(12, 0);
  scr.print("   ");
}

void resetMemPercent() {
  scr.setCursor(12, 1);
  scr.print("   ");
}
