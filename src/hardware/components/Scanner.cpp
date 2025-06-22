#include "Scanner.h"

#define SCANNER_DATA_PIN 6
#define LED_COUNT 10
#define SCAN_DELAY 100

Scanner::Scanner()
{
  _leds = new CRGB[LED_COUNT]; // allocate memory
  FastLED.addLeds<NEOPIXEL, SCANNER_DATA_PIN>(_leds, LED_COUNT);
}

void Scanner::start() { _running = true; }

void Scanner::stop()
{
  _running = false;

  for (int i = 0; i < LED_COUNT; i++)
    _leds[i] = CRGB::Black;

  FastLED.show();
}

void Scanner::update()
{
  if (!_running)
    return;

  unsigned long now = millis();
  if (now - _lastUpdate < SCAN_DELAY)
    return;

  _lastUpdate = now;

  if (_index == LED_COUNT - 1)
    _dir = -1;
  else if (_index == 0)
    _dir = 1;

  _trail.add(_index);

  _leds[_trail.get(3)] = CRGB::Black;
  _leds[_trail.get(2)] = CRGB::blend(CRGB::Red, CRGB::Black, 254);
  _leds[_trail.get(1)] = CRGB::blend(CRGB::Red, CRGB::Black, 248);
  _leds[_trail.get(0)] = CRGB::Red;

  _index += _dir;
  FastLED.show();
}

bool Scanner::running() { return _running; }