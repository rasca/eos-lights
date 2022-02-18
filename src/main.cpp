#include <config.h>
#include <man.h>
#include <wave.h>
#include <upper_fill.h>
#include <fade.h>


ManEffect manEffect;

void setup()
{

  Serial.begin(115200);
  Serial.println("Made with <3 by rasca");
  manEffect.setup();
  FastLED.setBrightness(255);
}

void loop()
{
    manEffect.tick();

    FastLED.show();
}