#ifndef __DIGITALPIN_H_
#define __DIGITALPIN_H_

#include <Arduino.h>
#include <stdint.h>

class DigitalPin
{
    private:
        int _pin;
        uint16_t *_OCR;
        uint16_t *_TCNT;
        uint8_t *_TCCRA;
        uint8_t *_TCCRB;
        uint8_t *_TIMSK;
        uint8_t *_TIFR;
    public:
        DigitalPin(int pin);
        int set_TCCRA(uint8_t reg);
        int set_TCCRB(uint8_t reg);
        int set_TCNT(uint16_t reg);
        int set_OCR(uint16_t reg);
        int factor_OCR(uint16_t reg);
        int set_TIMSK(uint8_t reg);
};

#endif

