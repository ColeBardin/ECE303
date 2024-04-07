#include "DigitalPin.h"

DigitalPin::timer_map_t tmap[NTIMERS] = 
{
    {0, TIMER_8BIT,  13, CH_A, TCCR0A, TCCR0B, TCNT0, OCR0A, TIMSK0, TIFR0},
    {0, TIMER_8BIT,   4, CH_B, TCCR0A, TCCR0B, TCNT0, OCR0B, TIMSK0, TIFR0},
    {1, TIMER_16BIT, 11, CH_A, TCCR1A, TCCR1B, TCNT1, OCR1A, TIMSK1, TIFR1},
    {1, TIMER_16BIT, 12, CH_B, TCCR1A, TCCR1B, TCNT1, OCR1B, TIMSK1, TIFR1},
    {2, TIMER_8BIT,  10, CH_A, TCCR2A, TCCR2B, TCNT2, OCR2A, TIMSK2, TIFR2},
    {2, TIMER_8BIT,   9, CH_B, TCCR2A, TCCR2B, TCNT2, OCR2B, TIMSK2, TIFR2},
    {3, TIMER_16BIT,  5, CH_A, TCCR3A, TCCR3B, TCNT3, OCR3A, TIMSK3, TIFR3},
    {3, TIMER_16BIT,  2, CH_B, TCCR3A, TCCR3B, TCNT3, OCR3B, TIMSK3, TIFR3},
    {3, TIMER_16BIT,  3, CH_C, TCCR3A, TCCR3B, TCNT3, OCR3C, TIMSK3, TIFR3},
    {4, TIMER_16BIT,  6, CH_A, TCCR4A, TCCR4B, TCNT4, OCR3A, TIMSK4, TIFR4},
    {4, TIMER_16BIT,  7, CH_B, TCCR4A, TCCR4B, TCNT4, OCR3B, TIMSK4, TIFR4},
    {4, TIMER_16BIT,  8, CH_C, TCCR4A, TCCR4B, TCNT4, OCR3C, TIMSK4, TIFR4},
    {5, TIMER_16BIT, 44, CH_A, TCCR5A, TCCR5B, TCNT5, OCR5A, TIMSK5, TIFR5},
    {5, TIMER_16BIT, 45, CH_B, TCCR5A, TCCR5B, TCNT5, OCR5B, TIMSK5, TIFR5},
    {5, TIMER_16BIT, 46, CH_C, TCCR5A, TCCR5B, TCNT5, OCR5C, TIMSK5, TIFR5},
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
            _TCNT = conf-> TCNT;
            _TCCRA = conf->TCCRA;
            _TCCRB = conf->TCCRB;
            _TIMSK = conf->TIMSK;
            _TIFR = conf->TIFR;
            set_TCNT(0);
            break;
        }
    }
}

int DigitalPin::set_TCCRA(uint8_t reg)
{
    return *_TCCRA = reg;
}

int DigitalPin::set_TCCRB(uint8_t reg)
{
    return *_TCCRB = reg;
}

int DigitalPin::set_TCNT(uint16_t reg)
{
    return *_TCNT = reg;
}

int DigitalPin::set_OCR(uint16_t reg)
{
    if(_width == TIMER_8BIT) return *(volatile uint8_t *)_OCR = reg;
    else return *_OCR = reg;
}

int DigitalPin::set_TIMSK(uint8_t reg)
{
    return *_TIMSK = reg;
}

int DigitalPin::factor_OCR(uint16_t factor)
{
    if(_width == TIMER_8BIT) return *(volatile uint8_t *)_OCR /= factor;
    else return *_OCR /= factor;
}

