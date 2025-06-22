#ifndef HARDWARE_H
#define HARDWARE_H

#include "components/Scanner.h"

class Hardware
{
public:
  Hardware();

  void init();
  void update();

  Scanner scanner;
};

extern Hardware hardware;

#endif