#include <Arduino.h>

int get_rand1k();

int number;
int attempt; 

void setup()
{
    number = get_rand1k();
    attempt = 1;
    Serial.begin(9600);
}

void loop()
{
    // blink at 1Hz
}

int get_rand1k()
{
    return 0;    
}

