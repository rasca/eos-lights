#ifndef WAVE_H_INCLUDED
#define WAVE_H_INCLUDED

#include <config.h>
#include <utils.h>

class Wave : public Effect
{
public:
  int hue = 0;
  int tail_num = 25;

  unsigned long startTime = 0;
  int duration = 1000;

  Wave(std::array<CRGB, NUM_LEDS> &leds, int tail_num) : Effect(leds), tail_num(tail_num) {}

  void setup()
  {
    startTime = millis();
  }

  void restart()
  {
    startTime = millis();
  }

  void tick()
  {
    int pos = std::min((int)(millis() - startTime) * NUM_LEDS / duration, NUM_LEDS);

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
    if (pos == NUM_LEDS)
    {
      startTime = millis();
      end();
    }
  }
};

#endif