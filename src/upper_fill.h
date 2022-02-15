#ifndef FILL_H_INCLUDED
#define FILL_H_INCLUDED

#include <config.h>
#include <utils.h>

class UpperFill : public Effect
{

public:
    int pos = 0;
    int hue = 0;
    int hue_variation = 30;

    UpperFill(std::array<CRGB, NUM_LEDS> &leds) : Effect(leds) {}
    UpperFill(std::array<CRGB, NUM_LEDS> &leds, int hue_variation) : Effect(leds), hue_variation(hue_variation) {}

    void tick()
    {

        leds[pos] = CHSV(hue, 255, 255);

        pos = (pos + 1) % NUM_LEDS;

        if (pos == 0)
        {
            end();
            hue = hue + 30 % 255;
        }
    }
};

#endif