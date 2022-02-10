#ifndef UPPER_FILL_H_INCLUDED
#define UPPER_FILL_H_INCLUDED

#include<config.h>
#include<utils.h>

int upper_pos = 0;
int upper_hue = 0;

void upper_fill() {
  if (upper_pos == 0) {
    FastLED.clear();
    upper_hue = upper_hue + 30 % 255;
  }
  upper_pos = (upper_pos + 1) % NUM_LEDS;

  leds[upper_pos] = CHSV(upper_hue, 255, 255);

  FastLED.show();

  delay(30);
}

#endif