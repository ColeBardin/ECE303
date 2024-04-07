#include <Arduino.h>
#include <DigitalPin.h>

int get_rand1k();

int number;
int attempt; 
DigitalPin leds[] =
{
   DigitalPin(11),
   DigitalPin(5),
   DigitalPin(6),
   DigitalPin(44)
};

void setup()
{
    number = get_rand1k();
    attempt = 1;
    Serial.begin(9600);
}

void loop()
{
    while(!Serial.available());
    // blink at 1Hz
}

int get_rand1k()
{
    return 0;    
}

