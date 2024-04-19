#include <Arduino.h>
#include "DigitalPin.h"

DigitalPin p(11);

void setup()
{
    Serial.begin(9600);
    DDRB = 0b00100000;
    //p.set_pin(GPIO_OUTPUT);
}

void loop()
{
    PORTB ^= 0b00100000;
    /*
    p.write(1);
    p.write(0);
    delay(5);
    */
}

