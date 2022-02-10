#ifndef WAVE_H_INCLUDED
#define WAVE_H_INCLUDED

#include<config.h>
#include<utils.h>

int pos = 0, hue = 0;

#define TAIL_NUM 25

void wave() {
  hue++;
  pos = (pos + 1) % NUM_LEDS;

  FastLED.clear();
  leds[pos] = CHSV(hue, 255, 255);

  for (int i = 1 ; i < TAIL_NUM; i++)
  {

    leds[wrap(pos-i)].r = leds[pos].r * pow(.75, i);
    leds[wrap(pos-i)].g = leds[pos].g * pow(.75, i);
    leds[wrap(pos-i)].b = leds[pos].b * pow(.75, i);

    leds[wrap(pos+i)].r = leds[pos].r * pow(.75, i);
    leds[wrap(pos+i)].g = leds[pos].g * pow(.75, i);
    leds[wrap(pos+i)].b = leds[pos].b * pow(.75, i);
  }
  Serial.println(pos);

  FastLED.show();
  delay(30);
}

#endif