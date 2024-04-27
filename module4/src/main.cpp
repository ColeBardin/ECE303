#include <Arduino.h>
#include "DigitalPin.h"
#include "AnalogPin.h"

#define PWM_TOP (int)12500
#define PMW_BOT (int)0 

AnalogPin a(A_0);
DigitalPin p(6);
int count;
int duty;

void setup()
{
    Serial.begin(9600);
    a.set_ref(0x1);
    a.set_prescaler(0x0);
    a.select_ADC();
    a.set_ADC(true);

    p.set_COM(COM_CLEAR);
    p.set_CS(CS_PS_1);
    p.set_WGN(0x0E);
    p.set_ICR(PWM_TOP);
    p.set_OCR(PMW_BOT);
    p.set_TCNT(0);
    p.set_pin(GPIO_OUTPUT);
    count = 0;
}

void loop()
{
    count = a.read(); 
    duty = (float)count * 100.0 / 1023.0;
    p.set_duty_cycle(duty); 
    /*
    Serial.print("duty ");
    Serial.println(duty);
    Serial.print("count ");
    Serial.println(p.read_OCR());
    */
    /*
    p.set_OCR(PWM_TOP * count / 100);
    count += 5;
    if(count > 99) count = 0;
    */
    delay(100);
}

