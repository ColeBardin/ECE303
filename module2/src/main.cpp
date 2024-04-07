#include <Arduino.h>
#include <DigitalPin.h>

int get_rand1k();

int number;
int attempt; 
DigitalPin p8(8);

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

