#ifndef MAN_H_INCLUDED
#define MAN_H_INCLUDED

#include <config.h>
#include <utils.h>
#include <fade.h>
#include <upper_fill.h>
#include <wave.h>
#include <composers.h>
#include <stars.h>
#include <beat.h>

class GrowFadeEffect : public BaseEffect
{

public:
    UpperFill arm1;
    UpperFill arm2;
    UpperFill arm3;
    UpperFill arm4;
    Wave head;
    Fade fade;
    const int total_effects = 5;

    GrowFadeEffect(std::array<std::array<CRGB, NUM_LEDS>, NUM_SEGMENTS> &segments) :
        arm1(segments[0]),
        arm2(segments[1]),
        arm3(segments[2]),
        arm4(segments[3]),
        head(segments[4], 15),
        fade(segments[0]) {}
    int step = 0;

    void setup()
    {
        arm1.endFunction = std::bind(&GrowFadeEffect::nextStep, this);
        arm2.endFunction = std::bind(&GrowFadeEffect::nextStep, this);
        arm3.endFunction = std::bind(&GrowFadeEffect::nextStep, this);
        arm4.endFunction = std::bind(&GrowFadeEffect::nextStep, this);
        fade.endFunction = std::bind(&GrowFadeEffect::nextStep, this);
    }

    void restart() {
        FastLED.clear();
            arm1.restart();
    }

    void nextStep()
    {
        step = (step + 1) % total_effects;
        switch (step)
        {
        case 0:
            arm1.restart();
            break;
        case 1:
            arm2.restart();
        case 2:
            arm3.restart();
            break;
        case 3:
            arm4.restart();
            break;
        case 4:
            fade.restart();
            break;
        }
        if (step == 0)
        {
            end();
        }
    }

    void tick()
    {
        switch (step)
        {
        case 0:
            // return wave;
            arm1.tick();
            break;
        case 1:
            arm2.tick();
            break;
        case 2:
            arm3.tick();
            break;
        case 3:
            arm4.tick();
            break;
        case 4:
            fade.tick();
            copyLeds(arm1.leds, arm2.leds);
            copyLeds(arm1.leds, arm3.leds);
            copyLeds(arm1.leds, arm4.leds);
            break;
        }
        head.tick();
    }
};

class WaveEffect : public BaseEffect
{
public:
    std::array<std::array<CRGB, NUM_LEDS>, NUM_SEGMENTS> &segments;
    Wave wave;

    int waveTotal = 3;
    int currentWave = 0;

    WaveEffect(std::array<std::array<CRGB, NUM_LEDS>, NUM_SEGMENTS> &segments)
        : segments(segments),
          wave(segments[4], 15) {}
    int step = 0;

    void setup()
    {
        wave.setup();
        wave.endFunction = std::bind(&WaveEffect::nextStep, this);
    }

    void nextStep()
    {
        currentWave = (currentWave + 1) % waveTotal;
        if (currentWave == 0)
        {
            end();
        }
    }

    void tick()
    {
        wave.tick();
        copyLeds(wave.leds, segments[0]);
        copyLeds(wave.leds, segments[1]);
        copyLeds(wave.leds, segments[2]);
        copyLeds(wave.leds, segments[3]);
    }
};

class ManEffect : public BaseEffect
{

public:
    std::array<std::array<CRGB, NUM_LEDS>, NUM_SEGMENTS> segments;

    GrowFadeEffect effect1;
    WaveEffect effect2;
    // Stars stars;

    ApplyToAll<Beat, int> beat;
    ApplyToAll<Stars, int> stars;

    int currentProgram = 0;
    int programsCount = 2;
    unsigned long currentTime = 0;

    ManEffect() : effect1(segments),
                  effect2(segments),
                  beat(segments, 10),
                  stars(segments, 10) {}

    void setup()
    {
        // Setup Segments
        // 4 legs/arms
        /*
        FastLED.addLeds<WS2812B, GPIO_NUM_18>(segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812B, GPIO_NUM_5>(segments[1].data(), NUM_LEDS);
        FastLED.addLeds<WS2812B, GPIO_NUM_17>(segments[2].data(), NUM_LEDS);
        FastLED.addLeds<WS2812B, GPIO_NUM_16>(segments[3].data(), NUM_LEDS);
        */
        FastLED.addLeds<WS2812, GPIO_NUM_15>(segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_2> (segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_0> (segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_4> (segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_16>(segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_17>(segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_5> (segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_18>(segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_19>(segments[0].data(), NUM_LEDS);

        // 1 head
        FastLED.addLeds<WS2812B, GPIO_NUM_4>(segments[4].data(), NUM_LEDS);

        effect1.setup();
        effect2.setup();
        stars.setup();
        beat.setup();
        effect1.endFunction = std::bind(&ManEffect::nextStep, this);
        effect2.endFunction = std::bind(&ManEffect::nextStep, this);
    }

/*
    BaseEffect& getCurrentEffect() {
        switch (currentProgram)
        {
        case 0:
            return effect1;
            break;
        case 1:
            return effect2;
            break;
        }
    }
    */


    void tick()
    {
        beat.tick();
        return;
        switch (currentProgram)
        {
        case 0:
            return effect2.tick();
            break;
        case 1:
            return effect2.tick();
            break;
        }
    }
    
    void nextStep() {
        if (millis() > currentTime + 1000)
        {
            currentTime = millis();
            currentProgram = (currentProgram + 1) % programsCount;
            switch (currentProgram)
            {
            case 0:
                return effect1.restart();
                break;
            case 1:
                return effect2.restart();
                break;
            }
        }
    }
};

#endif