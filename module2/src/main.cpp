#include "Safe.h"
#include <Arduino.h>

#define NLEDS 4
#define T1HZ 31250

Safe safe(2);
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

void set_LED(DigitalPin l, bool state);
void set_all_LED(bool state);
void freq_LED(DigitalPin l, float freq);
void freq_all_LED(float freq);

void setup()
{
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
    
    randomSeed(analogRead(0));
    int code = random(10000);
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
        case STATE_LOCK:
            Serial.println("Safe is LOCKED. Enter 4 digit number");
            while(!Serial.available());
            guess = Serial.readString().toInt();
            Serial.print("Trying code: ");
            Serial.println(guess);
            ret = safe.unlock(guess);
            switch(ret)
            {
                case -1:
                    set_all_LED(1);
                    state = STATE_FAIL;
                    Serial.println("Out of attempts");
                    break;
                case 0:
                    set_all_LED(0);
                    state = STATE_UNLOCK;
                    Serial.println("Success!");
                    break;
                default:
                    Serial.println("Incorrect");
                    break;
            }
            break;
        case STATE_UNLOCK:
            break;
        case STATE_FAIL:
            break;
        default:
            break;
    }
    //Serial.println("Safe is LOCKED. Enter 4 digit number");
    //safe.print();
    //p.print();
    //delay(1000);
    /*
    int guess;
    while(safe.on)
    {
        while(!Serial.available());
        guess = Serial.readString().toInt();
        Serial.print("Trying code: ");
        Serial.println(guess);
        if(!safe.unlock(guess))
        {
            Serial.println("Unlocked");   
            while(1) delay(10);
        }
        Serial.println("Incorrect. Try again");
    }
    Serial.println("Out of attempts :(");
    while(1) delay(10);
    */
}

void set_LED(DigitalPin l, bool state)
{
    noInterrupts();
    l.set_OCIE(false);
    digitalWrite(l._pin, state);
    interrupts();
}

void set_all_LED(bool state)
{
    for(int i = 0; i < NLEDS; i++) set_LED(l[i], state);
}

void freq_LED(DigitalPin l, float freq)
{
    noInterrupts();
    l.set_OCR((uint16_t)((float)T1HZ / freq));
    l.set_OCIE(true);
    interrupts();
}

void freq_all_LED(float freq)
{
    for(int i = 0; i < NLEDS; i++) freq_LED(l[i], freq);
}

ISR(TIMER5_COMPA_vect)
{
    static bool state = false;
    digitalWrite(44, state = !state);
}
ISR(TIMER1_COMPA_vect)
{
    static bool state = false;
    digitalWrite(11, state = !state);
}
ISR(TIMER4_COMPA_vect)
{
    static bool state = false;
    digitalWrite(6, state = !state);
}
ISR(TIMER3_COMPA_vect)
{
    static bool d5 = false;
    digitalWrite(5, d5 = !d5);
}

