#include "DigitalPin.h"

DigitalPin::DigitalPin(int pin) :
    _pin(pin)
{
    set_TCNT(0);
}

int set_TCCRA(uint8_t reg)
{
    return 0;
}

int set_TCCRB(uint8_t reg)
{
    return 0;
}

int set_TCNT(uint16_t reg)
{
    return 0;
}

int set_OCR(uint16_t reg)
{
    return 0;
}

int factor_OCR(uint16_t reg)
{
    return 0;
}

int set_TIMSK(uint8_t reg)
{
    return 0;
}

