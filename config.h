// config.h

#ifndef CONFIG_H
#define CONFIG_H

#include "buttons.h"

#define BUTTON_COUNT 10

void null_btn(lv_event_t *e) {
  ButtonSquare* self = static_cast<ButtonSquare*>(lv_event_get_user_data(e));
  if (self) {
    Serial.print("Button pressed: ");
    Serial.println(self->getLabel());
  }
}

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
  { "BAD DOLPHINS", RED, null_btn },
  { "NERVE GAS", YELLOW, null_btn},
  { "SHARKS", WHITE, null_btn},
  { "CUTE OTTERS", YELLOW, null_btn},
  { "EMERGENCY METH", GREEN, null_btn},
  { "SCARLETT JOHANSSON", RED, null_btn},
  { "BROWNIES", GREEN, null_btn},
  { "POT BROWNIES", GREEN, null_btn},
};

#endif