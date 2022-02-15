#ifndef WAVE_H_INCLUDED
#define WAVE_H_INCLUDED

#include <config.h>
#include <utils.h>

class Wave : public Effect
{
public:
  int pos = 0;
  int hue = 0;
  int tail_num = 25;

  Wave(CRGB (&leds)[NUM_LEDS], int tail_num) : Effect(leds), pos(tail_num), tail_num(tail_num) {}

  void tick()
  {

    leds[pos] = CHSV(hue, 255, 255);

    for (int i = 1; i < tail_num; i++)
    {

      leds[wrap(pos - i)].r = leds[pos].r * pow(.75, i);
      leds[wrap(pos - i)].g = leds[pos].g * pow(.75, i);
      leds[wrap(pos - i)].b = leds[pos].b * pow(.75, i);

      leds[wrap(pos + i)].r = leds[pos].r * pow(.75, i);
      leds[wrap(pos + i)].g = leds[pos].g * pow(.75, i);
      leds[wrap(pos + i)].b = leds[pos].b * pow(.75, i);
    }
    leds[wrap(pos - tail_num - 1)] = CRGB::Black;

    hue++;
    pos = (pos + 1) % NUM_LEDS;
    if (pos == tail_num)
    {
      end();
    }
  }
};

#endif