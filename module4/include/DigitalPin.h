#ifndef __DIGITALPIN_H_
#define __DIGITALPIN_H_

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>

#define NTIMERS 15
#define NDPINS 70

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

typedef enum
{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G,
    PORT_H,
    PORT_J,
    PORT_K,
    PORT_L
} port_t;
typedef enum
{
    GPIO_NULL,
    GPIO_OUTPUT,
    GPIO_INPUT,
} gpio_mode_t;

class DigitalPin
{
    public:
        int _ide;
        port_t _port;
        int _pin;
        int _timer;
        gpio_mode_t _mode;

        DigitalPin(int pin);
        //DigitalPin(port_t port, int pin);
        int set_pin(gpio_mode_t mode);
        void write(bool state);
        void toggle();
        bool read();
        int set_TCCRA(uint8_t reg);
        int set_TCCRB(uint8_t reg);
        int set_TCNT(uint16_t reg);
        int set_OCR(uint16_t reg);
        int set_TIMSK(uint8_t reg);
        int factor_OCR(float factor);
        int set_COM(com_t val);
        int set_CS(cs_t val);
        int set_WGN(uint8_t val);
        int set_OCIE(bool state);
        int set_TOIE(bool state);
        int set_ICIE(bool state);
        int set_ICR(uint16_t reg);
        int set_duty_cycle(float duty);
        void print();

        typedef struct
        {
            int pinIDE;
            port_t port;
            int pin;
            int PORTR;
        } dpin_map_t;
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
        bool _valid;
        bool _valid_timer;
        timer_ch _channel;
        timer_width _width;
        volatile uint8_t *_DDR;
        volatile uint8_t *_PORT;
        volatile uint8_t *_PIN;
        volatile uint8_t *_OCRL;
        volatile uint8_t *_OCRH;
        volatile uint8_t *_ICRL;
        volatile uint8_t *_ICRH;
        volatile uint8_t *_TCNTL;
        volatile uint8_t *_TCNTH;
        volatile uint8_t *_TCCRA;
        volatile uint8_t *_TCCRB;
        volatile uint8_t *_TIMSK;
        volatile uint8_t *_TIFR;
};

#endif

