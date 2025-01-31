#include <Arduino.h>
#include "DigitalPin.h"
#include "AnalogPin.h"

#define PWM_TOP 15684

AnalogPin a(A_0);
DigitalPin d(5);
int count;
int val;
int counter;

void setup()
{
    Serial.begin(9600);
    a.set_ref(0x1);
    a.set_prescaler(0x0);

    d.set_COM(COM_CLEAR);
    d.set_CS(CS_PS_1);
    d.set_WGN(0x0E);
    d.set_ICR(PWM_TOP);
    d.set_OCR(0);
    d.set_TCNT(0);
    d.set_pin(GPIO_OUTPUT);
    counter = 0;
}

void loop()
{
    if(Serial.available())
    {
        val = Serial.parseInt();
        d.set_duty_cycle((float)counter);
        delay(500);
        count = a.read(); 
        Serial.println(count);
        counter += 1;
        if(counter > 100) counter = 0;
    }
    delay(1);
}

