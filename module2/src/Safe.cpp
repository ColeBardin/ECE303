#include "Safe.h"

Safe::Safe(int attempts, int l0, int l1, int l2, int l3) :
    on(true),
    locked(false),
    tries(0),
    _code(0),
    _attempts(attempts),
    _duty(1),
    _l0(l0),
    _l1(l1),
    _l2(l2),
    _l3(l3)
{
    noInterrupts();
    _l0.set_TCCRA(0);
    _l0.set_TCCRB(0b00001000);
    _l0.set_TIMSK(0);
    _l0.set_COM(COM_TOGGLE);
    _l0.set_CS(CS_PS_256);
    //_l0.set_OCIE(true);
    _l0.set_OCR(T1HZ);

    _l1.set_TCCRA(0);
    _l1.set_TCCRB(0b00001000);
    _l1.set_TIMSK(0);
    _l1.set_COM(COM_TOGGLE);
    _l1.set_CS(CS_PS_256);
    //_l1.set_OCIE(true);
    _l1.set_OCR(T1HZ);
 
    _l2.set_TCCRA(0);
    _l2.set_TCCRB(0b00001000);
    _l2.set_TIMSK(0);
    _l2.set_COM(COM_TOGGLE);
    _l2.set_CS(CS_PS_256);
    //_l2.set_OCIE(true);
    _l2.set_OCR(T1HZ);

    _l3.set_TCCRA(0);
    _l3.set_TCCRB(0b00001000);
    _l3.set_TIMSK(0);
    _l3.set_COM(COM_TOGGLE);
    _l3.set_CS(CS_PS_256);
    //_l3.set_OCIE(true);
    _l3.set_OCR(T1HZ);
    interrupts();
}

int Safe::unlock(int code)
{
    if(!locked) return 0;
    int d0 = code % 10;
    int d1 = (code / 10) % 10;
    int d2 = (code / 100) % 10;
    int d3 = (code / 1000) % 10;
    int c0 = _code % 10;
    int c1 = (_code / 10) % 10;
    int c2 = (_code / 100) % 10;
    int c3 = (_code / 1000) % 10;

    if(code == _code)
    {
        set_LED(_l3, false); 
        set_LED(_l2, false); 
        set_LED(_l1, false); 
        set_LED(_l0, false); 
        locked = false;
        tries = 0;
        return 0;
    }

    if(++tries >= _attempts)
    {
        set_LED(_l3, true); 
        set_LED(_l2, true); 
        set_LED(_l1, true); 
        set_LED(_l0, true); 
        on = false;
        return 1;
    }

    if(d3 == c3) set_LED(_l3, false);
    else freq_LED(_l3, tries);
    if(d2 == c2) set_LED(_l2, false);
    else freq_LED(_l2, tries);
    if(d1 == c1) set_LED(_l1, false);
    else freq_LED(_l1, tries);
    if(d0 == c0) set_LED(_l0, false);
    else freq_LED(_l0, tries);

    return 1;
}

int Safe::lock()
{
    if(!on) return 1;
    if(!locked)
    {
        locked = true;
        tries = _attempts; 
    }
    return 0;
}

int Safe::set_code(int code)
{
    if(!on) return 1;
    if(locked) return 1;
    if(code > 9999 || code < 0) return 1;
    _code = code;
    return 0;
}

void Safe::freq_LED(DigitalPin l, int freq)
{
    l.set_OCIE(true);
    l.set_OCR(T1HZ / freq);
}

void Safe::set_LED(DigitalPin l, bool state)
{
    l.set_OCIE(false);
    digitalWrite(l._pin, state);
}
