#ifndef __ANALOGPIN_H_
#define __ANALOGPIN_H_

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>

#define NAPINS 16

typedef enum
{
    A_0,
    A_1,
    A_2,
    A_3,
    A_4,
    A_5,
    A_6,
    A_7,
    A_8,
    A_9,
    A_10,
    A_11,
    A_12,
    A_13,
    A_14,
    A_15,
} analogpin_number;

class AnalogPin 
{
    public:
        int _adc;
        uint16_t _count;

        AnalogPin(analogpin_number pin);
        //AnalogPin(port_t port, int pin);
        uint16_t read();
        int select_ADC();
        int set_ref(uint8_t ref);
        int set_ADC(bool state);
        int set_prescaler(uint8_t ps);
        int start_conv();
        uint16_t get_count();
        void print();
    private:
        bool _valid;
        volatile uint8_t *_ADMUX;
        volatile uint8_t *_ADCSRA;
        volatile uint8_t *_ADCSRB;
        volatile uint8_t *_ADCL;
        volatile uint8_t *_ADCH;
};

#endif

