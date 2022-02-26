#ifndef BEAT_H_INCLUDED
#define BEAT_H_INCLUDED

#include <config.h>
#include <utils.h>

class Beat : public Effect
{
public:
  int hue = 0;

  unsigned long startTime = 0;
  int duration = 10000;

  Beat(std::array<CRGB, NUM_LEDS> &leds, int param) : Effect(leds) {}

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
    int intensity = sin8(millis() / 25);
    if (intensity == 1)
    {
      hue += 20;
    }

    for (int i = 1; i < NUM_LEDS; i++)
    {
      leds[i] = CHSV(hue % 255, 255, intensity);
    }

    if (millis() - startTime > duration)
    {
      restart();
      end();
    }
  }
};

#endif