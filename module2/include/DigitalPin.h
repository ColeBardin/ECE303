#ifndef __DIGITALPIN_H_
#define __DIGITALPIN_H_

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

typedef enum
{
    COM_NORMAL,
    COM_TOGGLE,
    COM_CLEAR,
    COM_SET
} com_t;

typedef enum
{
    CS_DISABLE,
    CS_PS_1,
    CS_PS_8,
    CS_PS_64,
    CS_PS_256,
    CS_PS_1024,
    CS_EX_T1_FALLING,
    CS_EX_T1_RISING
} cs_t;

class DigitalPin
{
    public:
        bool _state;
        int _pin;
        int _timer;
        DigitalPin(int pin);
        void print();
        int set_TCCRA(uint8_t reg);
        int set_TCCRB(uint8_t reg);
        int set_TCNT(uint16_t reg);
        int set_OCR(uint16_t reg);
        int set_TIMSK(uint8_t reg);
        int factor_OCR(float factor);
        int set_COM(com_t val);
        int set_CS(cs_t val);
        int set_OCIE(bool state);
        int set_TOIE(bool state);
        int set_ICIE(bool state);
        void write(bool state);

        typedef struct
        {
            int timer;
            timer_width width;
            int pin;
            timer_ch channel;
            uint32_t TCCRA;
            uint32_t TCCRB;
            uint32_t TCNTL;
            uint32_t TCNTH;
            uint32_t OCRL;
            uint32_t OCRH;
            uint32_t TIMSK;
            uint32_t TIFR;
        } timer_map_t; 

    private:
        bool _valid_timer;
        timer_ch _channel;
        timer_width _width;
        uint32_t _OCRL;
        uint32_t _OCRH;
        uint32_t _TCNTL;
        uint32_t _TCNTH;
        uint32_t _TCCRA;
        uint32_t _TCCRB;
        uint32_t _TIMSK;
        uint32_t _TIFR;
};

#endif

