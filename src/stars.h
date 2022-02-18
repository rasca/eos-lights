#ifndef STARS_H_INCLUDED
#define STARS_H_INCLUDED

#include <math.h>
#include <algorithm>
#include <vector>
#include <config.h>
#include <utils.h>

class Star {
    public:
    int position;
    int duration;
    int brightness;
    int hue;
    unsigned long startTime = 0;

    Star () {
        setup();
    }

    void setup() {
        startTime = millis();
        position = random16(0, NUM_LEDS);
        brightness = random16(0, 10);
        hue = random16(0, 255);
        duration = random16(0, 255);
    }

    void restart() {
        setup();
    }

    CRGB tick() {
        int rnd = random16(0, 255);
        return CHSV(hue, 20, 10);
        switch (rnd) {
            // int starS = random8(0, 20) - 10 + 
            case 0 ... 3:
                return CHSV(hue, 20, brightness * 0.4);
            case 4 ... 30:
            case 31 ... 230:
                return CRGB::Black;
                return CHSV(hue, 30, random8(0, 20) - 10 + brightness);
            case 231 ... 254:
                return CRGB::Black;
                return CHSV(hue, 40, min(255, (int)(brightness * 1.3)));
            default:
                return CRGB::Black;
                return CHSV(hue, 60, min(255, (int)(brightness * 3)));
        }
    }
};

// Assign stars to leds
// Twinkle each star

class Stars : public Effect {

    public:
        unsigned long startTime = 0;
        int duration = 2000;
        int amount =  0;

        std::vector<Star> stars;

        Stars(std::array<CRGB, NUM_LEDS> &leds, int amount) : Effect(leds), amount(amount) {}

        void setup()
        {
            startTime = millis();
            for (int i=0; i<amount; i++) {
                stars.push_back(Star());
            }
        }

        void restart()
        {
            startTime = millis();
            for (auto& s: stars) {
                s.restart();
            }
        }

        void tick() {

            for (Star s : stars)
            {
                CRGB color = s.tick();
                leds[s.position] = color;
            }
        }
};

#endif
