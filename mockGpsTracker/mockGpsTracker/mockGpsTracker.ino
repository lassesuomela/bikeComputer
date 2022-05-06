#include <ArduinoJson.h>

DynamicJsonDocument data(64);

double lat, lng, alt, speed, hdop, course;
int sat;

void setup(){
  Serial.begin(115200);
}

void loop(){
    lat = random(6000000, 6600000) / 100000;
    lng = random(2400000, 2600000) / 100000;
    alt = random(20, 800);
    speed = random(0, 280) / 10;
    sat = random(3, 13);
    hdop = random(80, 1000);
    course = random(0, 360);
    
    data["lat"] = lat;
    data["lng"] = lng;
    data["speed"] = speed;
    data["course"] = course;
    data["altitude"] = alt;
    data["satellites"] = sat;
    data["hdop"] = hdop;
    
    serializeJson(data, Serial);
    Serial.println();
    
    delay(1000);
    
}
