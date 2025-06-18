#ifndef SCANNER_H
#define SCANNER_H

#ifndef SCANNER_DATA_PIN
#error "SCANNER_DATA_PIN must be defined before including Scanner.h"
#endif // SCANNER_DATA_PIN

#include <FastLED.h>
#include "../misc/Buffer.h"

class Scanner
{
public:
  Scanner(int led_count, CRGB color = CRGB::Red, int scan_delay = 100);
  void update();
  ~Scanner();

private:
  int LED_count;
  int index = 0;
  int dir = 1;
  int scan_delay; // in milliseconds
  unsigned long lastUpdate = 0;

  CRGB color;
  CRGB *leds;
  Buffer trail = Buffer(4);
};

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

#endif // SCANNER_H
