
#include <list>
#include <FastLED.h>

#define NUM_LEDS 50

CRGB leds[NUM_LEDS];

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

#define FRAME_TIME_MIN 10
#define FRAME_TIME_MAX 40
int frame_time = 30;
int velocity_direction = -1;

int pos = 0, hue = 0;

#define TAIL_NUM 25

int wrap(int pre) {
  if (pre < 0) {
    pre = pre + NUM_LEDS;
  } else if (pre > NUM_LEDS) {
    pre = pre - NUM_LEDS;
  }
  return pre;
}

void loop()
{

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
  frame_time = frame_time + velocity_direction;
  if (frame_time == FRAME_TIME_MAX || frame_time == FRAME_TIME_MIN) {
    velocity_direction = velocity_direction * -1;
  }
  delay(frame_time);
}