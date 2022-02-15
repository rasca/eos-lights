#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include<config.h>
#include <algorithm>
#include <iterator>
#include <functional>


class BaseEffect {
public:
  virtual void tick() = 0;
  void setup() {};
  void restart() {};
  void end()
  {
    Serial.println("base effect end");
    if (endFunction)
    {
      Serial.println("calling endFunction");
      endFunction();
    }
  }
  std::function<void()> endFunction;
};

class Effect : public BaseEffect {
    public:
        CRGB (&leds)[NUM_LEDS];
        Effect(CRGB (&leds)[NUM_LEDS]) : leds(leds) {}
};

int wrap(int pre) {
  if (pre < 0) {
    pre = pre + NUM_LEDS;
  } else if (pre > NUM_LEDS) {
    pre = pre - NUM_LEDS;
  }
  return pre;
}

void copyLeds(CRGB (&from)[NUM_LEDS], CRGB (&to)[NUM_LEDS]) {
  std::copy(std::begin(from), std::end(from), std::begin(to));
}

#endif