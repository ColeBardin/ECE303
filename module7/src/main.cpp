#include <Arduino.h>
#include "DigitalPin.h"

/* Experiment 5 */

#define PWM_TOP 15684
#define F_THRESH 30.0
#define M_THRESH 20.0
#define S_THRESH 10.0

typedef enum
{
    STATE_NULL,
    STATE_CLOSE,
    STATE_MEDIUM,
    STATE_FAR,
    STATE_GONE
} state_e;

void measure_dist();
void fsm_transition();
int spin_motor(int speed);
int dist_to_speed(float dist);

int val;
char temp;
unsigned long duration;
float cm;
state_e state;

DigitalPin r(2);
DigitalPin y(3);
DigitalPin g(4);
DigitalPin forward(5);
DigitalPin backward(6);
DigitalPin trig(11);
DigitalPin echo(12);

void setup()
{
    state = STATE_NULL;
    Serial.begin(9600);

    r.set_pin(GPIO_OUTPUT);
    y.set_pin(GPIO_OUTPUT);
    g.set_pin(GPIO_OUTPUT);
    r.write(0);
    y.write(0);
    g.write(0);

    backward.set_COM(COM_CLEAR);
    backward.set_CS(CS_PS_1);
    backward.set_WGN(0x0E);
    backward.set_ICR(PWM_TOP);
    backward.set_OCR(0);
    backward.set_TCNT(0);
    backward.set_pin(GPIO_OUTPUT);

    forward.set_COM(COM_CLEAR);
    forward.set_CS(CS_PS_1);
    forward.set_WGN(0x0E);
    forward.set_ICR(PWM_TOP);
    forward.set_OCR(0);
    forward.set_TCNT(0);
    forward.set_pin(GPIO_OUTPUT);

    trig.set_pin(GPIO_OUTPUT);
    trig.write(0);

    echo.set_pin(GPIO_INPUT);

    spin_motor(0);
}

void loop()
{
    measure_dist();
    fsm_transition();
    delay(500);
}

void measure_dist()
{
    trig.write(0);
    delayMicroseconds(5);
    trig.write(1);
    delayMicroseconds(10);
    trig.write(0);
    duration = pulseIn(12, HIGH);
    cm = ((float)duration / 2.0) / 29.1;
    Serial.print("Distance: ");
    Serial.print(cm);
    Serial.println(" cm");
}

void fsm_transition()
{
    int speed;
    if(cm > F_THRESH) state = STATE_GONE;
    else if(cm > M_THRESH) state = STATE_FAR;
    else if(cm > S_THRESH) state = STATE_MEDIUM;
    else state = STATE_CLOSE;

    Serial.print("State: ");
    Serial.println(state);

    switch(state)
    {
        case STATE_GONE:
            r.write(0);
            y.write(0);
            g.write(0);
            break;
        case STATE_FAR:
            r.write(1);
            y.write(0);
            g.write(0);
            break;
        case STATE_MEDIUM:
            r.write(1);
            y.write(1);
            g.write(0);
            break;
        case STATE_CLOSE:
            r.write(1);
            y.write(1);
            g.write(1);
            break;
        case STATE_NULL:
            break;
    }
    speed = dist_to_speed(cm);
    spin_motor(speed);
    Serial.print("Setting motor speed: ");
    Serial.print(speed);
    Serial.println("%");
}

int spin_motor(int speed)
{
    if(speed < -100) speed = -100;
    if(speed > 100) speed = 100;

    if(speed < 0)
    {
        forward.set_duty_cycle(0);
        backward.set_duty_cycle(-1 * speed);
    }
    else if(speed == 0)
    {
        forward.set_duty_cycle(0);
        backward.set_duty_cycle(0);
    }
    else if(speed > 0)
    {
        forward.set_duty_cycle(speed);
        backward.set_duty_cycle(0);
    }

    return 0;
}

int dist_to_speed(float dist)
{
    // S_THRESH and below -> 0
    // S_THRESH to F_THRESH maps from 45 to 100;    
    if(dist < S_THRESH) return 0;
    int speed = (int)map(dist, S_THRESH, F_THRESH, 45, 100);
    if(speed > 100) speed = 100;
    return speed;
}
