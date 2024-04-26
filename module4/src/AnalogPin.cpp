#include "AnalogPin.h"
#include <Arduino.h>

AnalogPin::AnalogPin(analogpin_number pin) :
    _adc(pin),
    _valid(false)
{
    if(pin >= NAPINS || pin < 0) return;
    _valid = true;
    _count = 0;
    _ADCL =   (volatile uint8_t *)0x78;
    _ADCH =   (volatile uint8_t *)0x79;
    _ADCSRA = (volatile uint8_t *)0x7A;
    _ADCSRB = (volatile uint8_t *)0x7B;
    _ADMUX =  (volatile uint8_t *)0x7C;
}

int AnalogPin::read()
{
    if(!_valid) return 1;
    select_ADC();
    set_ADC(true);
    start_conv();
    while(*_ADCSRA & 0x40);
    _count = get_count();
    set_ADC(false);
    return _count;
}

int AnalogPin::select_ADC()
{
    if(!_valid) return 1;
    *_ADMUX &= 0xE0;
    *_ADCSRB &= ~(1 << 3);
    uint8_t mux = (_adc & 0x7) + (_adc > 7 ? 0x20 : 0); 
    *_ADMUX |= mux & 0x1F;
    *_ADCSRB |= (mux >> 2) & 0x8;
    return 0;
}

int AnalogPin::set_ref(uint8_t ref)
{
    if(!_valid) return 1;
    *_ADMUX &= ~(0x3 << 6);
    *_ADMUX |= (ref & 0x3) << 6;
    return 0;
}

int AnalogPin::set_ADC(bool state)
{
    if(!_valid) return 1;
    if(state) *_ADCSRA |= 1 << 7;
    else *_ADCSRA &= ~(1 << 7);

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
    return (int)*_ADCL | (((int)*_ADCH) << 8);
}

void AnalogPin::print()
{
    Serial.print("A");
    Serial.println(_adc);

    Serial.print("ADMUX(0x");
    Serial.print((uint32_t)_ADMUX, HEX);
    Serial.print("): 0b");
    Serial.println(*_ADMUX, BIN);

    Serial.print("ADCSRA(0x");
    Serial.print((uint32_t)_ADCSRA, HEX);
    Serial.print("): 0b");
    Serial.println(*_ADCSRA, BIN);

    Serial.print("ADCSRB(0x");
    Serial.print((uint32_t)_ADCSRB, HEX);
    Serial.print("): 0b");
    Serial.println(*_ADCSRB, BIN);
}

