#include "Scanner.h"

Scanner::Scanner(int LED_count, CRGB color, int scan_delay)
    : LED_count(LED_count), color(color), scan_delay(scan_delay), index(0), dir(1)
{
  leds = new CRGB[LED_count]; // allocate memory
  FastLED.addLeds<NEOPIXEL, SCANNER_DATA_PIN>(leds, LED_count);
}

void Scanner::update()
{
  unsigned long now = millis();
  if (now - lastUpdate < scan_delay)
    return;

  lastUpdate = now;

  if (index == LED_count - 1)
    dir = -1;
  else if (index == 0)
    dir = 1;

  trail.add(index);

  leds[trail.get(3)] = CRGB::Black;
  leds[trail.get(2)] = CRGB::blend(color, CRGB::Black, 254);
  leds[trail.get(1)] = CRGB::blend(color, CRGB::Black, 248);
  leds[trail.get(0)] = color;

  index += dir;
  FastLED.show();
}

Scanner::~Scanner() { delete[] leds; }