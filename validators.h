#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <lvgl.h>

bool validate_48v(lv_event_t *e);
bool validate_motor(lv_event_t *e);
bool validate_inverter(lv_event_t *e);
bool validate_voice_mode(lv_event_t *e);

#endif
