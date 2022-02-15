#include <config.h>
#include <man.h>
#include <wave.h>
#include <upper_fill.h>
#include <fade.h>


ManEffect manEffect;

void setup()
{
  manEffect.setup();
  FastLED.setBrightness(255);
  Serial.begin(115200);
}

void loop()
{
    manEffect.tick();
    Serial.println("main tick");

    FastLED.show();
    delay(30);
}