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
DigitalPin::pin_map_t pmap[NPINS] = 
{
//  IDE  port   pin PORTR 
    { 0, PORT_E, 0, 0x2E},
    { 1, PORT_E, 1, 0x2E},
    { 2, PORT_E, 4, 0x2E},
    { 3, PORT_E, 5, 0x2E},
    { 4, PORT_G, 5, 0x34},
    { 5, PORT_E, 3, 0x2E},
    { 6, PORT_H, 3, 0x102},
    { 7, PORT_H, 4, 0x102},
    { 8, PORT_H, 5, 0x102},
    { 9, PORT_H, 6, 0x102},
    {10, PORT_B, 4, 0x25},
    {11, PORT_B, 5, 0x25},
    {12, PORT_B, 6, 0x25},
    {13, PORT_B, 7, 0x25},
    {14, PORT_J, 1, 0x105},
    {15, PORT_J, 0, 0x105},
    {16, PORT_H, 1, 0x102},
    {17, PORT_H, 0, 0x102},
    {18, PORT_D, 3, 0x2B},
    {19, PORT_D, 2, 0x2B},
    {20, PORT_D, 1, 0x2B},
    {21, PORT_D, 0, 0x2B},
    {22, PORT_A, 0, 0x22},
    {23, PORT_A, 1, 0x22},
    {24, PORT_A, 2, 0x22},
    {25, PORT_A, 3, 0x22},
    {26, PORT_A, 4, 0x22},
    {27, PORT_A, 5, 0x22},
    {28, PORT_A, 6, 0x22},
    {29, PORT_A, 7, 0x22},
    {30, PORT_C, 7, 0x28},
    {31, PORT_C, 6, 0x28},
    {32, PORT_C, 5, 0x28},
    {33, PORT_C, 4, 0x28},
    {34, PORT_C, 3, 0x28},
    {35, PORT_C, 2, 0x28},
    {36, PORT_C, 1, 0x28},
    {37, PORT_C, 0, 0x28},
    {38, PORT_D, 7, 0x2B},
    {39, PORT_G, 2, 0x34},
    {40, PORT_G, 1, 0x34},
    {41, PORT_G, 0, 0x34},
    {42, PORT_L, 7, 0x10B},
    {43, PORT_L, 6, 0x10B},
    {44, PORT_L, 5, 0x10B},
    {45, PORT_L, 4, 0x10B},
    {46, PORT_L, 3, 0x10B},
    {47, PORT_L, 2, 0x10B},
    {48, PORT_L, 1, 0x10B},
    {49, PORT_L, 0, 0x10B},
    {50, PORT_B, 3, 0x25},
    {51, PORT_B, 2, 0x25},
    {52, PORT_B, 1, 0x25},
    {53, PORT_B, 0, 0x25},
    {54, PORT_F, 0, 0x31},
    {55, PORT_F, 1, 0x31},
    {56, PORT_F, 2, 0x31},
    {57, PORT_F, 3, 0x31},
    {58, PORT_F, 4, 0x31},
    {59, PORT_F, 5, 0x31},
    {60, PORT_F, 6, 0x31},
    {61, PORT_F, 7, 0x31},
    {62, PORT_K, 0, 0x108},
    {63, PORT_K, 1, 0x108},
    {64, PORT_K, 2, 0x108},
    {65, PORT_K, 3, 0x108},
    {66, PORT_K, 4, 0x108},
    {67, PORT_K, 5, 0x108},
    {68, PORT_K, 6, 0x108},
    {69, PORT_K, 7, 0x108},
};

DigitalPin::DigitalPin(int pin) :
    _ide(pin),
    _valid(false),
    _valid_timer(false)
{
    if(pin >= NPINS || pin < 0) return;
    int i;

    _valid = true;
    pin_map_t pin_map = pmap[_ide];
    _port = pin_map.port;
    _pin = pin_map.pin;
    _PORT = (volatile uint8_t *)pin_map.PORTR;
    _DDR = (volatile uint8_t *)(pin_map.PORTR - 1);
    _PIN = (volatile uint8_t *)(pin_map.PORTR - 2);
    // TODO: set analog regs

    for(i = 0; i < NTIMERS; i++)
    {
        DigitalPin::timer_map_t *conf = &tmap[i];
        if(conf->pin == _ide)
        {
            _valid_timer = true;
            _timer = conf->timer;
            _channel = conf->channel;
            _width = conf->width;
            _OCRL = (volatile uint8_t *)conf->OCRL;
            _OCRH = (volatile uint8_t *)conf->OCRH;
            _TCNTL = (volatile uint8_t *)conf->TCNTL;
            _TCNTH = (volatile uint8_t *)conf->TCNTH;
            _TCCRA = (volatile uint8_t *)conf->TCCRA;
            _TCCRB = (volatile uint8_t *)conf->TCCRB;
            _TIMSK = (volatile uint8_t *)conf->TIMSK;
            _TIFR = (volatile uint8_t *)conf->TIFR;
            set_TCNT(0);
            return;
        }
    }
}
/*
DigitalPin::DigitalPin(port_t port, int pin)
{
    // TODO: fill out init function for PORT and PIN ctor
}
*/

int DigitalPin::set_pin(gpio_mode_t mode)
{
    _mode = mode;
// DDRX sets input vs output
    // 0 input, 1 output
    switch(mode)
    {
        case GPIO_NULL:
            return 1;
        case GPIO_OUTPUT:
            *_DDR |= (1 << _pin); 
            return 0;
        case GPIO_INPUT:
            *_DDR &= ~(1 << _pin); 
            return 0;
        case GPIO_ANALOG:
            // TODO: handle analog shiiz
            break;
    };
    return 0;
}

void DigitalPin::write(bool state)
{
    *_PORT &= ~(1 << _pin);
    *_PORT |= ((state & 0x1) << _pin);
}
void DigitalPin::toggle()
{
    *_PORT ^= (1 << _pin);
}

bool DigitalPin::read()
{
    return (*_PIN >> _pin) & 0x1;
}

uint16_t DigitalPin::readAnalog()
{
    return (0 & 1023);
}

int DigitalPin::set_TCCRA(uint8_t reg)
{
    if(_valid_timer) return *_TCCRA = reg;
    else return -1;
}

int DigitalPin::set_TCCRB(uint8_t reg)
{
    if(_valid_timer) return *_TCCRB = reg;
    else return -1;
}

int DigitalPin::set_TCNT(uint16_t reg)
{
    if(_valid_timer)
    {
        if(_width == TIMER_16BIT) *_TCNTH = reg >> 8;
        *_TCNTL = (uint8_t)reg;
        return reg;
    }
    else return -1;
}

int DigitalPin::set_OCR(uint16_t reg)
{
    if(_valid_timer)
    {
        if(_width == TIMER_16BIT) *_OCRH = reg >> 8;
        *_OCRL = (uint8_t)reg;
        return reg;
    }
    else return 1;
}

int DigitalPin::set_TIMSK(uint8_t reg)
{
    if(_valid_timer) return *_TIMSK = reg;
    else return -1;
}

int DigitalPin::factor_OCR(float factor)
{
    if(_valid_timer)
    {
        uint16_t ocr = *_OCRL;
        if(_width == TIMER_16BIT) ocr |= (uint16_t)(*_OCRH) << 8;
        ocr = (uint16_t)((float)ocr / factor);
        set_OCR(ocr);
        set_TCNT(0);
        return 0;
    }
    else return -1;
}

int DigitalPin::set_COM(com_t val)
{
    if(_valid_timer)
    {
        uint8_t tccra = *_TCCRA;
        tccra &= ~(0x3 << (6 - _channel * 2));
        tccra |= val << (6 - _channel * 2);
        return *_TCCRA = tccra;
    }
    else return -1;
}

int DigitalPin::set_CS(cs_t val)
{
    if(_valid_timer)
    {
        uint8_t tccrb = *_TCCRB;
        tccrb &= ~(0x7);
        tccrb |= val & 0x7;
        return *_TCCRB = tccrb;
    }
    else return -1;
}

int DigitalPin::set_WGN(uint8_t val)
{
    if(_valid_timer)
    {
        uint8_t tccra = *_TCCRA;
        uint8_t tccrb = *_TCCRB;

        tccra &= ~(0x3);
        tccra |= (val & 0x3);

        if(_width == TIMER_8BIT)
        {
            tccrb &= ~(0x1 << 3); 
            tccrb |= (val & 0x4) << 1;
        }
        else
        {
            tccrb &= ~(0x3 << 3); 
            tccrb |= (val & 0xC) << 1;
        }
        return 0;
    }
    else return 1;
}

int DigitalPin::set_OCIE(bool state)
{
    if(_valid_timer)
    {
        state &= 0x1;
        uint8_t timsk = *_TIMSK;
        timsk &= ~(0x1 << (_channel + 1));
        timsk |= state << (_channel + 1);
        return *_TIMSK = timsk;
    }
    else return -1;
}

int DigitalPin::set_TOIE(bool state)
{
    if(_valid_timer)
    {
        state &= 0x1;
        uint8_t timsk = *_TIMSK;
        timsk &= ~(0x1);
        timsk |= state;
        return *_TIMSK = timsk;
    }
    else return -1;
}

int DigitalPin::set_ICIE(bool state)
{
    if(_valid_timer)
    {
        state &= 0x1;
        uint8_t timsk = *_TIMSK;
        timsk &= ~(1 << 5);
        timsk |= state << 5;
        return *_TIMSK = timsk;
    }
    else return -1;
}

