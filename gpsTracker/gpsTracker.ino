#include <ArduinoJson.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


static const int RXPin = 3, TXPin = 4;

TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);

DynamicJsonDocument data(64);

double lat, lng, alt, speed, hdop, course;
int sat;

void setup(){
  Serial.begin(115200);
  ss.begin(9600);
}

void loop(){
  while (ss.available()){
    if (gps.location.isValid()){

      lat = gps.location.lat();  
      lng = gps.location.lng();
      alt = gps.altitude.meters();
      speed = gps.speed.kmph();
      sat = gps.satellites.value();
      hdop = gps.hdop.value();
      course = gps.course.deg();

      data["lat"] = lat;
      data["lng"] = lng;
      data["speed"] = speed;
      data["course"] = course;
      data["altitude"] = alt;
      data["satellites"] = sat;
      data["hdop"] = hdop;
        
      smartDelay(500);
    }
    else{
      data["error"] = "No GPS fix";
      
      smartDelay(10000);
    }

    serializeJson(data, Serial);
    Serial.println();

    data.clear();
  }
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
