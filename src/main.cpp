#include <config.h>
//#include <wave.h>
#include <upper_fill.h>

void setupMan() {
  // Setup Segments
  // 4 legs/arms
  FastLED.addLeds<WS2812B, GPIO_NUM_16>(leds_arm_1, NUM_LEDS);
  FastLED.addLeds<WS2812B, GPIO_NUM_4>(leds_arm_2, NUM_LEDS);
  FastLED.addLeds<WS2812B, GPIO_NUM_0>(leds_arm_3, NUM_LEDS);
  FastLED.addLeds<WS2812B, GPIO_NUM_2>(leds_arm_4, NUM_LEDS);
  
  // 1 head
  FastLED.addLeds<WS2812B, GPIO_NUM_15>(leds_head, NUM_LEDS);
}

void setup()
{
  setupMan();
  FastLED.setBrightness(255);
  Serial.begin(9600);
}

unsigned long current_time = 0;

UpperFill up1(leds_arm_1, 20);
UpperFill up2(leds_arm_2, 20);
UpperFill up3(leds_arm_3, 20);
UpperFill up4(leds_arm_4, 20);
// Wave wave(leds_arm_1, 5);

Effect& getCurrentEffect() {
  switch(programs_current) {
    case 0:
      // return wave;
      return up1;
      break;
    case 1:
      return up2;
      break;
    case 2:
      return up3;
      break;
    case 3:
      return up4;
      break;
  }
}

void loop()
{
  /*
  if (millis() > current_time + 3000) {
    current_time = millis();
    programs_current = (programs_current + 1) % programs_total;
  }
  */
    Effect& currentEffect = getCurrentEffect();

    currentEffect.tick();

    FastLED.show();
    delay(30);
}