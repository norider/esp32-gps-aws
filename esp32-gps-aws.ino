#include <TinyGPS++.h>
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
HardwareSerial hSerial2(2); // UART2 (RX=16, TX=17)

void setup()
{
  Serial.begin(115200);
  hSerial2.begin(GPSBaud);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (hSerial2.available() > 0)
    if (gps.encode(hSerial2.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  // Location
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  // Date
  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  // Time
  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  // Speed
  Serial.print(F("  Speed: "));
  if (gps.speed.isValid())
  {
    Serial.print(gps.speed.kmph()); // Speed in kilometers per hour (double)
    Serial.print(F("km/h"));
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  
  // course
  Serial.print(F("  Course: "));
  if (gps.course.isValid())
  {
    Serial.print(gps.course.deg()); // Course in degrees (double)
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  
  // altitude
  Serial.print(F("  Altitude: "));
  if (gps.altitude.isValid())
  {
    Serial.print(gps.altitude.meters()); // Altitude in meters (double)
    Serial.print(F("m"));
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  // satellites
  Serial.print(F("  Satellites: "));
  if (gps.satellites.isValid())
  {
    Serial.print(gps.satellites.value()); // Number of satellites in use (u32)
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  // horizontal diminution of precision
  Serial.print(F("  hdop: "));
  if (gps.hdop.isValid())
  {
    Serial.print(gps.hdop.value()); // Horizontal Dim. of Precision (100ths-i32)
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
