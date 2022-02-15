#ifndef FADE_H_INCLUDED
#define FADE_H_INCLUDED

#include<config.h>
#include<utils.h>

class Fade : public Effect {

    public:
        int step = 0;
        int totalSteps = 10;
        float scaleFactor = 0.7;

        Fade(CRGB (&leds)[NUM_LEDS]) : Effect(leds) {}

        void tick() {
            if (step == totalSteps - 1) {
                for (int i = 0; i < NUM_LEDS; i++)
                {
                    leds[i] = CRGB::Black;
                }
            } else {
                for (int i = 0; i < NUM_LEDS; i++)
                {
                    leds[i].r = leds[i].r * scaleFactor;
                    leds[i].g = leds[i].g * scaleFactor;
                    leds[i].b = leds[i].b * scaleFactor;
                }
            }

            step++;

            if (step == totalSteps) {
                step = 0;
                end();
            }
        }
};

#endif