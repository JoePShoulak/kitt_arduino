#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <lvgl.h>

bool validate_always(lv_event_t *e);

bool validate_cruise_mode(lv_event_t *e);
bool validate_motor(lv_event_t *e);
bool validate_48v(lv_event_t *e);
bool validate_inverter(lv_event_t *e);

#endif
