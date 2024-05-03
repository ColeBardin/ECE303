#include <Arduino.h>
#include "AnalogPin.h"

/* Experiment 2 */

AnalogPin a(A_0);
int count;
float volt;

void setup()
{
    Serial.begin(9600);
    a.set_ref(0x1);
    a.set_prescaler(0x0);
}

void loop()
{
    count = a.read(); 
    volt = (float)count * 5.0 / 1023.0;
    Serial.print("Read: ");
    Serial.print(volt);
    Serial.print("V (");
    Serial.print(count);
    Serial.println(" count)");
    delay(1000);
}

