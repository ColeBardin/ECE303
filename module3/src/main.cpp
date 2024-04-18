#include <Arduino.h>
#include "DigitalPin.h"

DigitalPin p(6);

void setup()
{
    Serial.begin(9600);
    p.set_pin(GPIO_OUTPUT);
    p.write(0);
}

void loop()
{
    while(!Serial.available());
    String a = Serial.readString();
    Serial.println("OFF - ON - OFF");
    p.write(0);
    p.write(1);
    p.write(0);
    delay(100);
    while(!Serial.available());
    a = Serial.readString();
    Serial.println("Toggle Toggle");
    p.write(0);
    p.toggle();
    p.toggle();
    delay(100);
}

