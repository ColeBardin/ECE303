#include <Arduino.h>
#include <LED.h>

LED::LED(int pin, String name) :
    _pin(pin),
    name(name)
{
    set_intensity(0);
}
void LED::on()
{
    set_intensity(255);
}

void LED::off()
{
    set_intensity(0);
}

void LED::set_intensity(int val)
{
    if(val < 0)   val = 0;
    if(val > 255) val = 255;
    _intensity = val;
    analogWrite(_pin, _intensity);
}

void LED::blink(int x, int y, int z)
{
    while(x-- > 0)
    {
        on();
        delay(y);
        off();
        delay(z);
    }
}

