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
    p.set_TCCRA(0b01000010);
    p.set_TCCRB(0b00001101);
    p.set_TIMSK(0b00000010);
    p.set_OCR(50000);
    /*
    p.set_COM(COM_TOGGLE);
    p.set_CS(CS_PS_1024);
    p.set_OCR(300);
    p.set_OCIE(1);
    */
    interrupts();
}

void loop()
{
    p.print();
    delay(1000);
    // blink at 1Hz
}

int get_rand1k()
{
    return 0;    
}

ISR(TIMER3_COMPA_vect)
{
    static bool state = false;
    //Serial.println("interrupt");
    digitalWrite(5, state = !state);
}
