#include <Arduino.h>
#include "DigitalPin.h"

/* Experiment 4 */

#define NLEDS 4
// PS 8 -> f 3.921 KHz
// 65535 / 3.921 = 16713 == 1 KHz
#define PWM_TOP 16713

DigitalPin pwm[NLEDS] =
{
    DigitalPin(12),
    DigitalPin(11),
    DigitalPin(6),
    DigitalPin(5),
};

float duty;

void setup()
{
    Serial.begin(9600);
    for(int i = 0; i < NLEDS; i++)
    {
        pwm[i].set_COM(COM_CLEAR);
        pwm[i].set_CS(CS_PS_8);
        pwm[i].set_WGN(0x0E);
        pwm[i].set_ICR(PWM_TOP);
        pwm[i].set_OCR(0);
        pwm[i].set_TCNT(0);
        pwm[i].set_pin(GPIO_OUTPUT);
    }
    duty = 5.0;
}

void loop()
{
    for(int i = 0; i < NLEDS; i++) pwm[i].set_duty_cycle(duty);
    duty += 5.0;
    if(duty > 95.0) duty = 5.0;
    Serial.println();

    Serial.print("Duty: ");
    Serial.print(duty);
    Serial.println("%");

    delay(1000);
}

