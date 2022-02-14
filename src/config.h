#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define NUM_LEDS 50

#include <FastLED.h>

CRGB leds_arm_1[NUM_LEDS];
CRGB leds_arm_2[NUM_LEDS];
CRGB leds_arm_3[NUM_LEDS];
CRGB leds_arm_4[NUM_LEDS];
CRGB leds_head[NUM_LEDS];

int programs_current = 0;
int programs_total = 4;

#endif