#ifndef FILL_H_INCLUDED
#define FILL_H_INCLUDED

#include<config.h>
#include<utils.h>

class UpperFill : public Effect {

    public:
        CRGB (&leds)[NUM_LEDS];
        int pos = 0;
        int hue = 0;
        int hue_variation = 30;

        UpperFill(CRGB (&leds)[NUM_LEDS], int hue_variation) : leds(leds), hue_variation(hue_variation) {}

        void setup() {
        }

        void tick() {
            Serial.println(hue_variation);

            pos = (pos + 1) % NUM_LEDS;

            if (pos == 0) {
                programs_current = (programs_current + 1) % programs_total;
                hue = hue + 30 % 255;
            }

            leds[pos] = CHSV(hue, 255, 255);

            FastLED.show();

            delay(30);
        }
};

#endif