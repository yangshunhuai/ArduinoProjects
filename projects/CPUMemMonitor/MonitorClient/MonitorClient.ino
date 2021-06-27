#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C scr(0x27, 16, 2);

int percentCPU = 0;
int percentMem = 0;
int blockCPU = 0;
int blockMem = 0;
String serialData;
char serialCharacter;
//bool completeSerial = false;
byte block[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  scr.init();
  scr.backlight();
  scr.createChar(0, block);
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
  printPercentCPU(percentCPU);
  printPercentMem(percentMem);
  printBlockMem(blockMem);
  printBlockCPU(blockCPU);

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
  translateIntoBlock(percentCPU, percentMem);
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

void translateIntoBlock(int valueCPU, int valueMem) {
  blockCPU = valueCPU / 15;
  blockMem = valueMem / 15;
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
    scr.write(byte(0));
  }
}

void printBlockMem(int blockMem) {
  resetBarMem();
  scr.setCursor(5, 1);
  int j = 0;
  for (j; j < blockMem; j++) {
    scr.write(byte());
  }
}

void printPercentCPU(int percentCPUPartial) {
  resetCPUPercent();
  scr.setCursor(12, 0);
  scr.print(percentCPUPartial);
}

void printPercentMem(int percentMemPartial) {
  resetMemPercent();
  scr.setCursor(12, 1);
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
