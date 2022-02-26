#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include<config.h>
#include <algorithm>
#include <iterator>
#include <functional>

int clamp(int x, int upper, int lower)
{
    return min(upper, max(x, lower));
}

class BaseEffect {
public:
  virtual void tick() = 0;
  void setup() {};
  void restart() {};
  void end()
  {
    if (endFunction)
    {
      endFunction();
    }
  }
  std::function<void()> endFunction;
};

class Effect : public BaseEffect {
    public:
        std::array<CRGB, NUM_LEDS> &leds;
        Effect(std::array<CRGB, NUM_LEDS> &leds) : leds(leds) {}
};

int wrap(int pre) {
  if (pre < 0) {
    pre = pre + NUM_LEDS;
  } else if (pre > NUM_LEDS) {
    pre = pre - NUM_LEDS;
  }
  return pre;
}

void copyLeds(std::array<CRGB, NUM_LEDS> &from, std::array<CRGB, NUM_LEDS> &to) {
  std::copy(std::begin(from), std::end(from), std::begin(to));
}

#endif