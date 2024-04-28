#include <Arduino.h>
#include "AnalogPin.h"
#include "DigitalPin.h"

// PS 8 -> f 3.921 KHz
// 65535 / 3.921 = 16713 == 1 KHz
#define PWM_TOP 16713

AnalogPin a(A_0);
DigitalPin d(6);
int count;
float volt;

void setup()
{
    Serial.begin(9600);
    a.set_ref(0x1);
    a.set_prescaler(0x0);
    a.select_ADC();
    a.set_ADC(true);

    d.set_COM(COM_CLEAR);
    d.set_CS(CS_PS_8);
    d.set_WGN(0x0E);
    d.set_ICR(PWM_TOP);
    d.set_OCR(0);
    d.set_TCNT(0);
    d.set_pin(GPIO_OUTPUT);
}

void loop()
{
    count = a.read(); 
    volt = (float)count * 5.0 / 1023.0;
    Serial.print("Read: ");
    Serial.print(count);
    Serial.print(" (");
    Serial.print(volt);
    Serial.println("V)");
    delay(1000);
}

