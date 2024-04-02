#include <Arduino.h>
#include <LED.h>

LED::LED(int pin, String name) :
    _pin(pin),
    name(name)
{
    _intensity = 255;
}
void LED::on()
{
    _intensity = 255;
    analogWrite(_pin, _intensity);
}

void LED::off()
{
    _intensity = 0;
    analogWrite(_pin, _intensity);
}

void LED::intensity(int val)
{
    if(val < 0)   val = 0;
    if(val > 255) val = 255;
    _intensity = val;
    analogWrite(_pin, _intensity);
}

void LED::blink(int x, int y, int z)
{
}
