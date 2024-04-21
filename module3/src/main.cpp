#include <Arduino.h>
#include "DigitalPin.h"

DigitalPin p(11);

void setup()
{
    Serial.begin(9600);
    p.set_pin(GPIO_OUTPUT);
    p.write(0);
}

void loop()
{
    p.write(1);
    p.write(0);
    delay(5);
}

