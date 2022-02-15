#ifndef MAN_H_INCLUDED
#define MAN_H_INCLUDED

#include <config.h>
#include <utils.h>
#include <fade.h>
#include <upper_fill.h>
#include <wave.h>

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

    GrowFadeEffect(CRGB (&arm1)[NUM_LEDS],
                   CRGB (&arm2)[NUM_LEDS],
                   CRGB (&arm3)[NUM_LEDS],
                   CRGB (&arm4)[NUM_LEDS],
                   CRGB (&head)[NUM_LEDS]) : arm1(arm1),
                                             arm2(arm2),
                                             arm3(arm3),
                                             arm4(arm4),
                                             head(head, 15),
                                             fade(arm1) {}
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
    }

    void nextStep()
    {
        Serial.println("man end");
        step = (step + 1) % total_effects;
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
    CRGB (&arm1)
    [NUM_LEDS];
    CRGB (&arm2)
    [NUM_LEDS];
    CRGB (&arm3)
    [NUM_LEDS];
    CRGB (&arm4)
    [NUM_LEDS];
    CRGB (&head)
    [NUM_LEDS];
    Wave wave;

    int waveTotal = 3;
    int currentWave = 0;

    WaveEffect(CRGB (&arm1)[NUM_LEDS],
               CRGB (&arm2)[NUM_LEDS],
               CRGB (&arm3)[NUM_LEDS],
               CRGB (&arm4)[NUM_LEDS],
               CRGB (&head)[NUM_LEDS]) : arm1(arm1),
                                         arm2(arm2),
                                         arm3(arm3),
                                         arm4(arm4),
                                         head(head),
                                         wave(head, 15) {}
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
        copyLeds(wave.leds, arm1);
        copyLeds(wave.leds, arm2);
        copyLeds(wave.leds, arm3);
        copyLeds(wave.leds, arm4);
    }
};

class ManEffect : public BaseEffect
{

public:
    CRGB leds_arm_1[NUM_LEDS];
    CRGB leds_arm_2[NUM_LEDS];
    CRGB leds_arm_3[NUM_LEDS];
    CRGB leds_arm_4[NUM_LEDS];
    CRGB leds_head[NUM_LEDS];

    GrowFadeEffect effect1;
    WaveEffect effect2;

    int currentProgram = 0;
    int programsCount = 2;
    unsigned long currentTime = 0;

    ManEffect() : effect1(leds_arm_1, leds_arm_2, leds_arm_3, leds_arm_4, leds_head),
                  effect2(leds_arm_1, leds_arm_2, leds_arm_3, leds_arm_4, leds_head) {}

    void setup()
    {
        // Setup Segments
        // 4 legs/arms
        FastLED.addLeds<WS2812B, GPIO_NUM_16>(leds_arm_1, NUM_LEDS);
        FastLED.addLeds<WS2812B, GPIO_NUM_4>(leds_arm_2, NUM_LEDS);
        FastLED.addLeds<WS2812B, GPIO_NUM_0>(leds_arm_3, NUM_LEDS);
        FastLED.addLeds<WS2812B, GPIO_NUM_2>(leds_arm_4, NUM_LEDS);

        // 1 head
        FastLED.addLeds<WS2812B, GPIO_NUM_15>(leds_head, NUM_LEDS);

        effect1.setup();
        effect2.setup();
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
        switch (currentProgram)
        {
        case 0:
            return effect1.tick();
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