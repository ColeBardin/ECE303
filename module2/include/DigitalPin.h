#ifndef __DIGITALPIN_H_
#define __DIGITALPIN_H_

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>

#define NTIMERS 15

typedef enum 
{
    CH_A,
    CH_B,
    CH_C
} timer_ch;

typedef enum
{
    TIMER_8BIT,
    TIMER_16BIT
} timer_width;

class DigitalPin
{
    public:
        DigitalPin(int pin);
        int set_TCCRA(uint8_t reg);
        int set_TCCRB(uint8_t reg);
        int set_TCNT(uint16_t reg);
        int set_OCR(uint16_t reg);
        int set_TIMSK(uint8_t reg);
        int factor_OCR(uint16_t factor);

        typedef struct
        {
            int timer;
            timer_width width;
            int pin;
            timer_ch channel;
            uint8_t *TCCRA;
            uint8_t *TCCRB;
            uint16_t *TCNT;
            uint16_t *OCR;
            uint8_t *TIMSK;
            uint8_t *TIFR;
        } timer_map_t; 

    private:
        int _pin;
        int _timer;
        bool _valid_timer;
        timer_ch _channel;
        timer_width _width;
        volatile uint16_t *_OCR;
        volatile uint16_t *_TCNT;
        volatile uint8_t *_TCCRA;
        volatile uint8_t *_TCCRB;
        volatile uint8_t *_TIMSK;
        volatile uint8_t *_TIFR;
};

#endif

