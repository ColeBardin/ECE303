#ifndef _LED_H_
#define _LED_H_

class LED
{
    private:
        int _pin;
        int _intensity;
    public:
        String name;
        LED(int pin, String name);
        void on();
        void off();
        void set_intensity(int val);
        void blink(int x, int y, int z);
};

#endif // _LED_H_

