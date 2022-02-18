#ifndef FILL_H_INCLUDED
#define FILL_H_INCLUDED

#include <config.h>
#include <utils.h>
#include <algorithm>

class UpperFill : public Effect
{


public:
    int pos = 0;
    int hue = 0;
    int hue_variation = 30;

    unsigned long startTime = 0;
    int duration = 1000;

    UpperFill(std::array<CRGB, NUM_LEDS> &leds) : Effect(leds) {}
    UpperFill(std::array<CRGB, NUM_LEDS> &leds, int hue_variation) : Effect(leds), hue_variation(hue_variation) {}

    void setup() {
        startTime = millis();
    }

    void restart() {
        startTime = millis();
    }

    void tick()
    {
        int elapsed = std::min((int)(millis() - startTime) * NUM_LEDS / duration, NUM_LEDS);

        leds[elapsed] = CHSV(hue, 255, 255);

        if (elapsed == NUM_LEDS)
        {
            startTime = millis();
            end();
            hue = hue + 30 % 255;
        }
    }
};

#endif