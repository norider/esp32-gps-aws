#include <TinyGPS++.h>
#include <ArduinoJson.h>

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
      toJson();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void toJson()
{
  StaticJsonBuffer<256> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["deviceid"] = 0;

  JsonObject& gpsinfo = root.createNestedObject("gpsinfo");
  gpsinfo["device"] = "eps32";
  gpsinfo["time"] = String(gps.date.year()) + "-" + String(gps.date.month()) + "-" + String(gps.date.day()) + "T" + String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()) + "." + String(gps.time.centisecond());
  gpsinfo["lat"] = gps.location.lat(), 6;
  gpsinfo["lon"] = gps.location.lng(), 6;
  gpsinfo["alt"] = gps.altitude.meters();
  gpsinfo["track"] = gps.course.deg();
  gpsinfo["speed"] = gps.speed.kmph();

  char JSONmessageBuffer[256];
  root.printTo(JSONmessageBuffer);
//  root.prettyPrintTo(JSONmessageBuffer);
  Serial.println(JSONmessageBuffer);
}

