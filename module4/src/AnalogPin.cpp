#include "AnalogPin.h"
#include <Arduino.h>

AnalogPin::AnalogPin(analogpin_number pin) :
    _adc(pin),
    _valid(false)
{
    if(pin >= NAPINS || pin < 0) return;
    _valid = true;
    _ADCL =   (volatile uint8_t *)0x78;
    _ADCH =   (volatile uint8_t *)0x79;
    _ADCSRA = (volatile uint8_t *)0x7A;
    _ADCSRB = (volatile uint8_t *)0x7B;
    _ADMUX =  (volatile uint8_t *)0x7C;
}

int AnalogPin::read()
{
    if(!_valid) return 1;
    set_ADC(true);
    start_conv();
    while(*_ADCSRA & 0x40);
    return 0;
}

int AnalogPin::select_ADC()
{
    if(!_valid) return 1;
    uint8_t mux = (_adc & 0x7) + (_adc > 7 ? 0x20 : 0); 
    *_ADMUX |= mux & 0x1F;
    *_ADCSRB |= (mux >> 2) & 0x8;
    return 0;
}

int AnalogPin::set_REF(uint8_t ref)
{
    if(!_valid) return 1;
    *_ADMUX |= (ref & 0x3) << 6;
    return 0;
}

int AnalogPin::set_ADC(bool state)
{
    if(!_valid) return 1;
    *_ADCSRA |= (state & 0x1) << 7;
    return 0;
}

int AnalogPin::set_prescaler(uint8_t ps)
{
    if(!_valid) return 1;
    *_ADCSRA |= ps & 0x7;
    return 0;
}

int AnalogPin::start_conv()
{
    if(!_valid) return 1;
    *_ADCSRA |= 1 << 6; 
    return 0;
}

int AnalogPin::get_count()
{
    if(!_valid) return -1;
    return *_ADCL | (*_ADCH << 8);
}

