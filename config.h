// config.h

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "buttons.h"

#define BUTTON_COUNT 8

void null_btn(lv_event_t *e); // basic debug callback

const ButtonData button_panel1[BUTTON_COUNT] = {
  { "TURBO BOOST", RED, null_btn },
  { "MAP SYSTEM", YELLOW, null_btn},
  { "SKI MODE", WHITE, null_btn},
  { "VOLTAGE OUTPUT", YELLOW, null_btn},
  { "VITAL SCAN", GREEN, null_btn},
  { "EVADE", GREEN, null_btn},
  { "RANGE BRITE", GREEN, null_btn},
  { "RADAR IMAGE", GREEN, null_btn},
};

const ButtonData button_panel2[BUTTON_COUNT] = {
  { "RUDE DOLPHINS", RED, null_btn },
  { "NERVE GAS", YELLOW, null_btn},
  { "SHARKS", WHITE, null_btn},
  { "CUTE OTTERS", YELLOW, null_btn},
  { "EMERGENCY METH", GREEN, null_btn},
  { "SCARLETT JOHANSSON", RED, null_btn},
  { "BROWNIES", GREEN, null_btn},
  { "POT BROWNIES", GREEN, null_btn},
};

#endif