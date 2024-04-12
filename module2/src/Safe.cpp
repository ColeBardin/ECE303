#include "Safe.h"

Safe::Safe(int attempts) :
    on(true),
    locked(false),
    tries(0),
    _code(0),
    _attempts(attempts),
    _duty(1)
{
}

int Safe::unlock(int code)
{
    if(!locked) return 0;
    int g[4];
    int c[4];
    g[0] = code % 10;
    g[1] = (code / 10) % 10;
    g[2] = (code / 100) % 10;
    g[3] = (code / 1000) % 10;
    c[0] = _code % 10;
    c[1] = (_code / 10) % 10;
    c[2] = (_code / 100) % 10;
    c[3] = (_code / 1000) % 10;

    int ret = 0;
    for(int i = 0; i < 4; i++) ret |= (g[i] != c[i]) << i;
    if(ret) if(++tries >= _attempts) return -1;
    return ret;
}

int Safe::lock()
{
    if(!on) return 1;
    if(!locked)
    {
        locked = true;
        tries = 0;
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
