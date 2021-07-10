#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Device defines
#define CLOCK_IO 4
#define CLOCK_CLK 5
#define CLOCK_CE 2
#define DHTTYPE DHT11
#define DHTPIN 7

ThreeWire myWire(CLOCK_IO, CLOCK_CLK, CLOCK_CE); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
LiquidCrystal_I2C scr(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup ()
{
  Serial.begin(9600);
  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  scr.init();
  scr.backlight();
  scr.setCursor(0, 0);
  scr.print("Initializing,");
  scr.setCursor(0, 1);
  scr.print("Please wait.");

  dht.begin();

  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTimeDHT(compiled);
  Serial.println();

  if (!Rtc.IsDateTimeValid())
  {
    // Common Causes:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing

    Serial.println("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }

  if (Rtc.GetIsWriteProtected())
  {
    Serial.println("RTC was write protected, enabling writing now");
    Rtc.SetIsWriteProtected(false);
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
    Serial.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled)
  {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }
}

void loop ()
{
  RtcDateTime now = Rtc.GetDateTime();

  printDateTimeDHT(now);
  Serial.println();

  if (!now.IsValid())
  {
    // Common Causes:
    //    1) the battery on the device is low or even missing and the power line was disconnected
    Serial.println("RTC lost confidence in the DateTime!");
  }
  delay(1000); // one sec
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTimeDHT(const RtcDateTime& dt)
{
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  char datestr[20];
  snprintf(datestr, sizeof(datestr), "%04u/%02u/%02u", dt.Year(), dt.Month(), dt.Day());

  char timestr[20];
  snprintf(timestr, sizeof(timestr), "%02u:%02u:%02u", dt.Hour(), dt.Minute(), dt.Second());
  Serial.println(datestr);
  Serial.println(timestr);
  scr.clear();
  scr.setCursor(0, 0);
  scr.print(datestr);
  if (isnan(temp))
  {
  }
  else
  {
    scr.print(" T");
    scr.print(temp);
  }
  scr.setCursor(0, 1);
  scr.print(timestr);
  if (isnan(humidity))
  {
  }
  else
  {
    scr.print("   H");
    scr.print(humidity);
  }
}
