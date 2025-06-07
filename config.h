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

const ButtonData button_data[BUTTON_COUNT] = {
  { "TURBO BOOST", RED, null_btn },
  { "MAP SYSTEM", YELLOW, null_btn},
  { "SKI MODE", WHITE, null_btn},
  { "VOLTAGE OUTPUT", YELLOW, null_btn},
  { "VITAL SCAN", GREEN, null_btn},
  { "EVADE", GREEN, null_btn},
  { "RANGE BRITE", GREEN, null_btn},
  { "RADAR IMAGE", GREEN, null_btn},
};

#endif