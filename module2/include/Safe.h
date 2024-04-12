#ifndef _SAFE_H_
#define _SAFE_H_

#include <Arduino.h>
#include "DigitalPin.h"

class Safe
{
    public:
        bool on;
        bool locked;
        int tries;
        Safe(int attempts);
        int unlock(int code);
        int lock(); 
        int set_code(int code);
        void print();
    private:
        int _code;
        int _attempts; 
        int _duty;
};

#endif // _SAFE_H_

