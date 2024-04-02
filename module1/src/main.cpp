#include <Arduino.h>
#include <LED.h>

#define DEBUG 1
#define DELIM ','

LED leds[] = {
              LED(8, "red"), 
              LED(7, "yellow"), 
              LED(6, "blue"), 
              LED(5, "green")
             };

void setup()
{

    Serial.begin(9600);
}

void loop()
{
    while(!Serial.available());
    String led_color = Serial.readStringUntil(DELIM);
    if(led_color == NULL)
    {
        Serial.println("ERROR: failed parsing led color");
        return;
    }
    led_color.toLowerCase();
    led_color.trim();
    for(auto &l: leds)
    {
        if(led_color.equals(l.name))
        {
            String cmd = Serial.readStringUntil(DELIM);
            if(cmd == NULL)
            {
                Serial.println("ERROR: failed parsing cmd");
                Serial.println("format: led,cmd,optargs");
                return;
            }
            cmd.toLowerCase();
            cmd.trim();
            if(cmd.equals("on"))
            {
                #if DEBUG==1
                String tmp = led_color + " set on";
                Serial.println(tmp);
                #endif
                l.on();
            }
            else if(cmd.equals("off"))
            {
                #if DEBUG==1
                String tmp = led_color + " set off";
                Serial.println(tmp);
                #endif
                l.off();
            }
            else if(cmd.equals("blink"))
            {
                String tmp = Serial.readStringUntil(DELIM);
                if(tmp == NULL)
                {
                    Serial.println("ERROR: failed parsing blink times");
                    Serial.println("format: led,blink,times,on_ms,off_ms");
                    return;
                }
                int x = tmp.toInt();
                tmp = Serial.readStringUntil(DELIM);
                if(tmp == NULL)
                {
                    Serial.println("ERROR: failed parsing blink on_ms");
                    Serial.println("format: led,blink,times,on_ms,off_ms");
                    return;
                }
                int y = tmp.toInt();
                tmp = Serial.readStringUntil(DELIM);
                if(tmp == NULL)
                {
                    Serial.println("ERROR: failed parsing blink off_ms");
                    Serial.println("format: led,blink,times,on_ms,off_ms");
                    return;
                }
                int z = tmp.toInt();
                #if DEBUG==1
                tmp = led_color + " blink " + x + " times " + y + "ms on " + z + "ms off";
                Serial.println(tmp);
                #endif
                for(int cnt = 0; cnt < x; cnt++)
                {
                    l.on();
                    delay(y);
                    l.off();
                    delay(z);
                }
            }
            else
            {
                Serial.println("ERROR: cmd not found: " + cmd);
            }
            return;
        }
    }
    Serial.println("ERROR: led color name invalid: " + led_color);
}

