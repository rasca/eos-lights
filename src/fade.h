#ifndef FADE_H_INCLUDED
#define FADE_H_INCLUDED

#include <math.h>
#include <algorithm>
#include<config.h>
#include<utils.h>

class Fade : public Effect {

    public:
        int step = 0;
        int totalSteps = 10;
        float scaleFactor = 0.7;


        unsigned long startTime = 0;
        int duration = 2000;
        int lastStep = 0;

        std::array<CRGB, NUM_LEDS> initialCopy;

        Fade(std::array<CRGB, NUM_LEDS> &leds) : Effect(leds), initialCopy(leds) {}

        void setup()
        {
            startTime = millis();
            lastStep = 0;
            initialCopy = leds;
        }

        void restart()
        {
            startTime = millis();
            lastStep = 0;
            initialCopy = leds;
        }

        void tick() {

            unsigned long currentTime = millis();
            if (currentTime >= startTime + duration) {
                Serial.println("blacken");
                for (int i = 0; i < NUM_LEDS; i++)
                {
                    leds[i] = CRGB::Black;
                }
                end();
            }
            else
            {
                for (int i = 0; i < NUM_LEDS; i++)
                {
                    double elapsed = (1.0 * millis() - startTime) / duration; // between [0,1]

                    leds[i].r = initialCopy[i].r * (1 - elapsed);
                    leds[i].g = initialCopy[i].g * (1 - elapsed);
                    leds[i].b = initialCopy[i].b * (1 - elapsed);
                }
            }
        }
};

#endif