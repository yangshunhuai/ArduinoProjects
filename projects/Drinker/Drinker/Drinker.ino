#include <SPI.h>
#include <MFRC522.h>

#define RST 9
#define SS 10

MFRC522 reader(RST, SS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {};
  SPI.begin();
  reader.PCD_Init();
}

void loop() {
  // put your main code here, to run repeatedly:

}
