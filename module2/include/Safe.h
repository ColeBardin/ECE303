#ifndef _SAFE_H_
#define _SAFE_H_

#include <Arduino.h>
#include "DigitalPin.h"

#define T1HZ 31250

class Safe
{
    public:
        bool on;
        bool locked;
        int tries;
        Safe(int attempts, int l0, int l1, int l2, int l3);
        int unlock(int code);
        int lock(); 
        int set_code(int code);
    private:
        int _code;
        int _attempts; 
        int _duty;
        DigitalPin _l0;
        DigitalPin _l1;
        DigitalPin _l2;
        DigitalPin _l3;
        void freq_LED(DigitalPin l, int freq);
        void set_LED(DigitalPin l, bool state);
};
#endif // _SAFE_H_

