#ifndef _SAFE_H_
#define _SAFE_H_

#include <Arduino.h>
#include "DigitalPin.h"

class Safe
{
    public:
        Safe();
    private:
        _attempts; 
        _code;
        DigitalPin _l0;
        DigitalPin _l1;
        DigitalPin _l2;
        DigitalPin _l3;
};
#endif // _SAFE_H_

