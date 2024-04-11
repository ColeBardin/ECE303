#include "DigitalPin.h"
#include <Arduino.h>

DigitalPin::timer_map_t tmap[NTIMERS] = 
{
//   t  width       pin  ch   tccra   tccrb  cnt    ocr    timks tifr 
    {0, TIMER_8BIT,  13, CH_A, 0x44,  0x45,  0x46,  0x47,  0x6E, 0x35},
    {0, TIMER_8BIT,   4, CH_B, 0x44,  0x45,  0x46,  0x47,  0x6E, 0x35},
    {1, TIMER_16BIT, 11, CH_A, 0x80,  0x81,  0x84,  0x88,  0x6F, 0x36},
    {1, TIMER_16BIT, 12, CH_B, 0x80,  0x81,  0x84,  0x8A,  0x6F, 0x36},
    {2, TIMER_8BIT,  10, CH_A, 0xB0,  0xB1,  0xB2,  0xB3,  0x70, 0x37},
    {2, TIMER_8BIT,   9, CH_B, 0xB0,  0xB1,  0xB2,  0xB4,  0x70, 0x37},
    {3, TIMER_16BIT,  5, CH_A, 0x90,  0x91,  0x94,  0x98,  0x71, 0x38},
    {3, TIMER_16BIT,  2, CH_B, 0x90,  0x91,  0x94,  0x9A,  0x71, 0x38},
    {3, TIMER_16BIT,  3, CH_C, 0x90,  0x91,  0x94,  0x9C,  0x71, 0x38},
    {4, TIMER_16BIT,  6, CH_A, 0xA0,  0xA1,  0xA4,  0xA8,  0x72, 0x39},
    {4, TIMER_16BIT,  7, CH_B, 0xA0,  0xA1,  0xA4,  0xAA,  0x72, 0x39},
    {4, TIMER_16BIT,  8, CH_C, 0xA0,  0xA1,  0xA4,  0xAC,  0x72, 0x39},
    {5, TIMER_16BIT, 44, CH_A, 0x120, 0x121, 0x124, 0x128, 0x73, 0x3A},
    {5, TIMER_16BIT, 45, CH_B, 0x120, 0x121, 0x124, 0x12A, 0x73, 0x3A},
    {5, TIMER_16BIT, 46, CH_C, 0x120, 0x121, 0x124, 0x12C, 0x73, 0x3A},
};

DigitalPin::DigitalPin(int pin) :
    _pin(pin),
    _valid_timer(false)
{
    for(int i = 0; i < NTIMERS; i++)
    {
        DigitalPin::timer_map_t *conf = &tmap[i];
        if(conf->pin == _pin)
        {
            _valid_timer = true;
            _timer = conf->timer;
            _channel = conf->channel;
            _width = conf->width;
            _OCR = conf->OCR;
            _TCNT = conf->TCNT;
            _TCCRA = conf->TCCRA;
            _TCCRB = conf->TCCRB;
            _TIMSK = conf->TIMSK;
            _TIFR = conf->TIFR;
            set_TCNT(0);
            return;
        }
    }
}

int DigitalPin::set_TCCRA(uint8_t reg)
{
    return *((volatile byte *)_TCCRA) = reg;
}

int DigitalPin::set_TCCRB(uint8_t reg)
{
    return *((volatile byte *)_TCCRB) = reg;
}

int DigitalPin::set_TCNT(uint16_t reg)
{
    if(_width == TIMER_8BIT) return *(volatile byte *)_TCNT = reg;
    else 
    {
        *((volatile byte *)_TCNT) = (uint8_t)reg;
        *((volatile byte *)(_TCNT + 1)) = (uint8_t)(reg >> 8);
        return reg;
    }
}

int DigitalPin::set_OCR(uint16_t reg)
{
    if(_width == TIMER_8BIT) return *(volatile byte *)_OCR = reg;
    else 
    {
        *((volatile byte *)_OCR) = (uint8_t)reg;
        *((volatile byte *)(_OCR + 1)) = (uint8_t)(reg >> 8);
        return reg;
    }
}

int DigitalPin::set_TIMSK(uint8_t reg)
{
    return *((volatile byte *)_TIMSK) = reg;
}

int DigitalPin::factor_OCR(uint16_t factor)
{
    return 0;
    /*
    if(_width == TIMER_8BIT) return *(volatile uint8_t *)_OCR /= factor;
    else return *(volatile uint16_t *)_OCR /= factor;
    */
}

int DigitalPin::set_COM(com_t val)
{
    *(volatile byte *)_TCCRA &= ~(0x3 << (7 - _channel * 2));
    return *(volatile byte *)_TCCRA |= val << (7 - _channel * 2);
}

int DigitalPin::set_CS(cs_t val)
{
   *(volatile byte *)_TCCRB &= ~0x7; 
   return *(volatile byte *)_TCCRB |= val;
}

int DigitalPin::set_OCIE(bool state)
{
    state &= 0x1;
    *(volatile byte *)_TIMSK &= ~(0x1 << (_channel + 1));
    return *(volatile byte *)_TIMSK |= state << (_channel + 1);
}

int DigitalPin::set_TOIE(bool state)
{
    state &= 0x1;
    *(volatile byte *)_TIMSK &= ~(0x1);
    return *(volatile byte *)_TIMSK |= state;
}

int DigitalPin::set_ICIE(bool state)
{
    state &= 0x1;
    *(volatile byte *)_TIMSK &= ~(1 << 5);
    return *(volatile byte *)_TIMSK |= state << 5;
}

void DigitalPin::print()
{
    Serial.println("~~~~~~~~~~~~~~");
    Serial.print("pin ");
    Serial.println(_pin);
    Serial.print("timer ");
    Serial.println(_timer);
    Serial.print("valid timer ");
    Serial.println(_valid_timer);
    Serial.print("channel ");
    Serial.println(_channel);
    Serial.print("width ");
    Serial.println(_width);
    if(_width == TIMER_16BIT){
        uint16_t ocr = *((volatile byte *)(_OCR + 1));
        Serial.print("ocrh ");
        Serial.println(ocr);
        uint16_t ocrl = *(volatile byte *)_OCR;
        Serial.print("ocrl ");
        Serial.println(ocrl);

        uint16_t tcnt = *(volatile byte *)(_TCNT + 1);
        uint16_t tcntl = *(volatile byte*)_TCNT;
        Serial.print("tcnt ");
        Serial.println((tcnt << 8) | tcntl);
    }else{
        Serial.print("ocr ");
        Serial.println(*(volatile byte *)_OCR);
        Serial.print("tcnt ");
        Serial.println(*(volatile byte *)_TCNT);
    }
    Serial.print("tccra ");
    Serial.println(*(volatile byte *)_TCCRA);
    Serial.print("tccrb ");
    Serial.println(*(volatile byte *)_TCCRB);
    Serial.print("timsk ");
    Serial.println(*(volatile byte *)_TIMSK);
    Serial.print("tift ");
    Serial.println(*(volatile byte *)_TIFR);
}

