#include <Arduino.h>
#include <DigitalPin.h>

int get_rand1k();

int number;
int attempt; 
/*
DigitalPin leds[] =
{
   DigitalPin(11),
   DigitalPin(5),
   DigitalPin(6),
   DigitalPin(44)
};
*/

DigitalPin p(5);

void setup()
{
    Serial.begin(9600);
    number = get_rand1k();
    noInterrupts();
    p.set_TCCRA(0b00000000);
    p.set_TCCRB(0b00001000);
    p.set_TIMSK(0);
    p.set_COM(COM_TOGGLE);
    p.set_CS(CS_PS_256);
    p.set_OCIE(1);
    p.set_OCR(64000);
    interrupts();
}

void loop()
{
    //p.print();
    p.set_OCR(64000);
    for(int i = 0; i < 4; i++)
    {
        p.factor_OCR(2);
        delay(5000);
    }
    // blink at 1Hz
}

int get_rand1k()
{
    return 0;    
}

ISR(TIMER3_COMPA_vect)
{
    static bool state = false;
    digitalWrite(5, state = !state);
}
