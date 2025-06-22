#ifndef SCANNER_H
#define SCANNER_H

#include <FastLED.h>

#include "../../misc/Buffer.h"

class Scanner
{
public:
  Scanner();

  void start();
  void stop();
  void update();

  bool running();

private:
  int _index = 0;
  int _dir = 1;
  unsigned long _lastUpdate = 0;
  bool _running = false;

  CRGB *_leds;
  Buffer _trail = Buffer(4);
};

#endif // SCANNER_H
