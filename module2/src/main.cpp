#include "Safe.h"
#include <Arduino.h>

#define NLEDS 4
#define T1HZ 31250

Safe safe(5);
DigitalPin l[] = 
{
    DigitalPin(5),
    DigitalPin(6),
    DigitalPin(11),
    DigitalPin(44)
};
typedef enum
{
    STATE_NULL,
    STATE_LOCK,
    STATE_UNLOCK,
    STATE_FAIL
} state_t;
state_t state = STATE_NULL;
int code;

int try_again();
void set_LED(DigitalPin l, bool state);
void set_all_LED(bool state);
void freq_LED(DigitalPin l, float freq);
void freq_all_LED(float freq);

void setup()
{
    randomSeed(analogRead(0));
    Serial.begin(9600);
    for(int i = 0; i < NLEDS; i++)
    {
        l[i].set_TCCRA(0);
        l[i].set_TCCRB(0b00001000);
        l[i].set_TIMSK(0);
        l[i].set_COM(COM_TOGGLE);
        l[i].set_CS(CS_PS_256);
        freq_LED(l[i], 1);
    }
    code = random(10000);
    Serial.print("Setting safe code to: ");
    Serial.println(code);
    safe.set_code(code);
    safe.lock();
    state = STATE_LOCK;
}

void loop()
{
    int guess;
    int ret;
    switch(state)
    {
        case STATE_NULL:
            Serial.println("ERROR: cannot run in STATE_NULL");
            while(1) delay(10);
            break;
        case STATE_LOCK:
            Serial.println("Safe is LOCKED. Enter 4 digit number");
            while(!Serial.available());
            guess = Serial.readString().toInt();
            Serial.print("Trying code: ");
            Serial.println(guess);
            ret = safe.unlock(guess);
            if(ret == -1)
            {
                Serial.println("Out of attempts");
                set_all_LED(1);
                state = STATE_FAIL;
            }
            else if(ret == 0)
            {
                Serial.println("Success!");
                set_all_LED(0);
                state = STATE_UNLOCK;
            }
            else
            {
                Serial.println("Incorrect");
                set_all_LED(0);
                delay(100);
                for(int i = 0; i < NLEDS; i++)
                {
                    if(ret & (0x1 << i)) freq_LED(l[i], safe.tries + 1);
                    else set_LED(l[i], 0);
                }
            }
            break;
        case STATE_UNLOCK:
            Serial.println("Unlocked");
        case STATE_FAIL:
            if(try_again()) break;
            else while(1) delay(10);
            break;
    }
}

int try_again()
{
    Serial.println("Reset code and try again? [y/n]");
    while(!Serial.available());
    String resp = Serial.readString();
    resp.toLowerCase();
    resp.trim();
    Serial.print("input: ");
    Serial.println(resp);
    if(resp.equals("y"))
    {
        safe._force_reset();
        code = random(10000);
        Serial.print("Setting safe code to: ");
        Serial.println(code);
        safe.set_code(code);
        safe.lock();
        state = STATE_LOCK;
        freq_all_LED(1);
        return 1;
    }
    Serial.println("Bye :(");
    return 0;
}

void set_LED(DigitalPin l, bool state)
{
    l.set_OCIE(false);
    l.write(state);
}

void set_all_LED(bool state)
{
    noInterrupts();
    for(int i = 0; i < NLEDS; i++) set_LED(l[i], state);
    interrupts();
}

void freq_LED(DigitalPin l, float freq)
{
    l.set_OCR((uint16_t)((float)T1HZ / freq));
    l.set_TCNT(0);
    l.set_OCIE(true);
}

void freq_all_LED(float freq)
{
    noInterrupts();
    for(int i = 0; i < NLEDS; i++) freq_LED(l[i], freq);
    interrupts();
}

ISR(TIMER5_COMPA_vect)
{
    l[3].write(!l[3]._state);
}
ISR(TIMER1_COMPA_vect)
{
    l[2].write(!l[2]._state);
}
ISR(TIMER4_COMPA_vect)
{
    l[1].write(!l[1]._state);
}
ISR(TIMER3_COMPA_vect)
{
    l[0].write(!l[0]._state);
}

