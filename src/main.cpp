#include <config.h>
#include <wave.h>
#include <upper_fill.h>

void setupMan() {
  // Setup Segments
  // 4 legs/arms
  FastLED.addLeds<WS2812B, GPIO_NUM_15>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, GPIO_NUM_2>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, GPIO_NUM_0>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, GPIO_NUM_4>(leds, NUM_LEDS);
  
  // 1 head
  FastLED.addLeds<WS2812B, GPIO_NUM_16>(leds, NUM_LEDS);
}

void setup()
{
  setupMan();
  FastLED.setBrightness(255);
  Serial.begin(9600);
}

unsigned long current_time = 0;
int programs_current = 0;
int programs_total = 2;

UpperFill up(20);
Wave wave(5);

Effect& getCurrentEffect() {
  switch(programs_current) {
    case 0:
      return wave;
      break;
    case 1:
      return up;
      break;
  }
}

void loop()
{
  if (millis() > current_time + 10000) {
    current_time = millis();
    programs_current = (programs_current + 1) % programs_total;
  }
    Effect& currentEffect = getCurrentEffect();

    currentEffect.tick();

    FastLED.show();
    delay(30);
}