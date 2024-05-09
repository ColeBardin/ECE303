#include <Arduino.h>
#include "DigitalPin.h"
#include "AnalogPin.h"

/* Experiment 1 */

#define PWM_TOP 15684

AnalogPin a(A_0);
DigitalPin d(5);
int count;
float volt;
int duty;

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
    duty = 5;
}

void loop()
{
    count = a.read(); 
    volt = (float)count * 5.0 / 1023.0;
    d.set_duty_cycle(duty);
    //Serial.print("Read: ");
    Serial.println(volt);
    //Serial.print("V (");
    //Serial.print(count);
    //Serial.println(" count)");

    delay(2000);

    duty += 5;
    if(duty > 95) duty = 5;
}

