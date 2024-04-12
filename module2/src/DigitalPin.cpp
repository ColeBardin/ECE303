#include "DigitalPin.h"
#include <Arduino.h>

DigitalPin::timer_map_t tmap[NTIMERS] = 
{
//   t  width       pin  ch   tccra   tccrb  tcntl  tcnth  ocrl   ocrh   timks tifr 
    {0, TIMER_8BIT,  13, CH_A, 0x44,  0x45,  0x46,  NULL,  0x47,  NULL,  0x6E, 0x35},
    {0, TIMER_8BIT,   4, CH_B, 0x44,  0x45,  0x46,  NULL,  0x48,  NULL,  0x6E, 0x35},
    {1, TIMER_16BIT, 11, CH_A, 0x80,  0x81,  0x84,  0x85,  0x88,  0x89,  0x6F, 0x36},
    {1, TIMER_16BIT, 12, CH_B, 0x80,  0x81,  0x84,  0x85,  0x8A,  0x8B,  0x6F, 0x36},
    {2, TIMER_8BIT,  10, CH_A, 0xB0,  0xB1,  0xB2,  NULL,  0xB3,  NULL,  0x70, 0x37},
    {2, TIMER_8BIT,   9, CH_B, 0xB0,  0xB1,  0xB2,  NULL,  0xB4,  NULL,  0x70, 0x37},
    {3, TIMER_16BIT,  5, CH_A, 0x90,  0x91,  0x94,  0x95,  0x98,  0x99,  0x71, 0x38},
    {3, TIMER_16BIT,  2, CH_B, 0x90,  0x91,  0x94,  0x95,  0x9A,  0x9B,  0x71, 0x38},
    {3, TIMER_16BIT,  3, CH_C, 0x90,  0x91,  0x94,  0x95,  0x9C,  0x9D,  0x71, 0x38},
    {4, TIMER_16BIT,  6, CH_A, 0xA0,  0xA1,  0xA4,  0xA5,  0xA8,  0xA9,  0x72, 0x39},
    {4, TIMER_16BIT,  7, CH_B, 0xA0,  0xA1,  0xA4,  0xA5,  0xAA,  0xAB,  0x72, 0x39},
    {4, TIMER_16BIT,  8, CH_C, 0xA0,  0xA1,  0xA4,  0xA5,  0xAC,  0xAD,  0x72, 0x39},
    {5, TIMER_16BIT, 44, CH_A, 0x120, 0x121, 0x124, 0x125, 0x128, 0x129, 0x73, 0x3A},
    {5, TIMER_16BIT, 45, CH_B, 0x120, 0x121, 0x124, 0x125, 0x12A, 0x12B, 0x73, 0x3A},
    {5, TIMER_16BIT, 46, CH_C, 0x120, 0x121, 0x124, 0x125, 0x12C, 0x12D, 0x73, 0x3A},
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
            _OCRL = conf->OCRL;
            _OCRH = conf->OCRH;
            _TCNTL = conf->TCNTL;
            _TCNTH = conf->TCNTH;
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
    if(_width == TIMER_16BIT) *(volatile byte *)_TCNTH = reg >> 8;
    *((volatile byte *)_TCNTL) = (uint8_t)reg;
    return reg;
}

int DigitalPin::set_OCR(uint16_t reg)
{
    if(_width == TIMER_16BIT) *(volatile byte *)_OCRH = reg >> 8;
    *((volatile byte *)_OCRL) = (uint8_t)reg;
    return reg;
}

int DigitalPin::set_TIMSK(uint8_t reg)
{
    return *((volatile byte *)_TIMSK) = reg;
}

int DigitalPin::factor_OCR(float factor)
{
    uint16_t ocr = *(volatile byte *)_OCRL;
    if(_width == TIMER_16BIT) ocr |= (uint16_t)(*(volatile byte *)_OCRH) << 8;
    ocr = (uint16_t)((float)ocr / factor);
    set_OCR(ocr);
    set_TCNT(0);
    return 0;
}

int DigitalPin::set_COM(com_t val)
{
    uint8_t tccra = *(volatile byte *)_TCCRA;
    tccra &= ~(0x3 << (6 - _channel * 2));
    tccra |= val << (6 - _channel * 2);
    return *(volatile byte *)_TCCRA = tccra;
}

int DigitalPin::set_CS(cs_t val)
{
    uint8_t tccrb = *(volatile byte *)_TCCRB;
    tccrb &= ~(0x7);
    tccrb |= val & 0x7;
    *(volatile byte *)_TCCRB = tccrb;
    return tccrb;
}

int DigitalPin::set_OCIE(bool state)
{
    state &= 0x1;
    uint8_t timsk = *(volatile byte *)_TIMSK;
    timsk &= ~(0x1 << (_channel + 1));
    timsk |= state << (_channel + 1);
    return *(volatile byte *)_TIMSK = timsk;
}

int DigitalPin::set_TOIE(bool state)
{
    state &= 0x1;
    uint8_t timsk = *(volatile byte *)_TIMSK;
    timsk &= ~(0x1);
    timsk |= state;
    return *(volatile byte *)_TIMSK = timsk;
}

int DigitalPin::set_ICIE(bool state)
{
    state &= 0x1;
    uint8_t timsk = *(volatile byte *)_TIMSK;
    timsk &= ~(1 << 5);
    timsk |= state << 5;
    return *(volatile byte *)_TIMSK = timsk;
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
    if(_width == TIMER_8BIT)
    {
        Serial.print("&ocr 0x");
        Serial.println(_OCRL, HEX);
        Serial.print("&tcnt 0x");
        Serial.println(_TCNTL, HEX);
    }
    else
    {
        uint16_t ocr = *(volatile byte *)_OCRL;
        ocr |= ((uint16_t)(*(volatile byte *)_OCRH)) << 8;
        Serial.print("ocr ");
        Serial.print(ocr);
        Serial.print(" @ L0x");
        Serial.println(_OCRL, HEX);
        uint16_t tcnt = *(volatile byte *)_TCNTL;
        tcnt |= ((uint16_t)(*(volatile byte *)_TCNTH)) << 8;
        Serial.print("tcnt ");
        Serial.print(tcnt );
        Serial.print(" @ L0x");
        Serial.println(_TCNTL, HEX);
    }
    Serial.print("tccra 0b");
    Serial.print(*(volatile byte *)_TCCRA, BIN);
    Serial.print(" @ 0x");
    Serial.println(_TCCRA, HEX);
    Serial.print("tccrb 0b");
    Serial.print(*(volatile uint8_t *)_TCCRB, BIN);
    Serial.print(" @ 0x");
    Serial.println(_TCCRB, HEX);
    Serial.print("timsk 0b");
    Serial.print(*(volatile byte *)_TIMSK, BIN);
    Serial.print(" @ 0x");
    Serial.println(_TIMSK, HEX);
    Serial.print("tift 0b");
    Serial.print(*(volatile byte *)_TIFR, BIN);
    Serial.print(" @ 0x");
    Serial.println(_TIFR, HEX);
}

