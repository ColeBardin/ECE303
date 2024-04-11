#include <Arduino.h>
#include "Safe.h"

Safe safe(5, 44, 11, 6, 5);

void setup()
{
    Serial.begin(9600);
    randomSeed(analogRead(0));
    int code = random(10000);
    Serial.print("Setting safe code to: ");
    Serial.println(code);
    safe.set_code(code);
}

void loop()
{
    safe.lock();
    Serial.println("Safe is LOCKED. Enter 4 digit number");
    int guess;
    while(safe.on)
    {
        while(!Serial.available());
        guess = Serial.parseInt();
        if(!safe.unlock(guess))
        {
            Serial.println("Unlocked");   
            while(1) delay(10);
        }
        Serial.println("Incorrect. Try again");
    }
    Serial.println("Out of attempts :(");
    while(1) delay(10);
}

/*
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
    static bool state = false;
    digitalWrite(5, state = !state);
}
*/
