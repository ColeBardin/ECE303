#include <Arduino.h>
//#include "DigitalPin.h"
#include "AnalogPin.h"

AnalogPin a(12);
int count;

void setup()
{
    Serial.begin(9600);
    a.set_ref(0x1);
    a.set_prescaler(0x0);
    a.select_ADC();
    a.set_ADC(true);
}

void loop()
{
    a.print();
    count = a.read(); 
    Serial.print("ADC count: ");
    Serial.println(count);
    delay(1000);
}

