#include <Arduino.h> // for Serial

#include "button.h"
#include "config.h"
#include "popup.h"
#include "voice_tile.h"

// This file implements the callbacks and validation logic declared in
// config.h. Functions are grouped by purpose for clarity.

// ==== Basic callbacks ====
void null_btn(lv_event_t *e) {
  Button *self = static_cast<Button *>(lv_event_get_user_data(e));
  if (self) {
    if (self->isToggleable()) {
      Serial.print("Button ");
      Serial.print(self->isToggled() ? "On: " : "Off: ");
    } else {
      Serial.print("Button pressed: ");
    }
    Serial.println(self->getLabel());
  }
}

void motor_override_cb(lv_event_t *e) {
  Serial.println("MOTOR override callback!");
}

void voice_mode_cb(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  if (!self || !self->isToggled() || !voiceTile)
    return;
  for (int i = 0; i < 3; ++i) {
    Button *other = voiceTile->getButton(i);
    if (other && other != self && other->isToggled()) {
      other->handlePress();
    }
  }
}

// ==== Validation helpers ====
bool validate_24v(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  if (!self)
    return true;
  if (!self->isToggled() && motor_btn && motor_btn->isToggled()) {
    Serial.println("ERROR: Cannot activate 24V MODE while MOTOR is ON");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    if (grid) {
      lv_obj_t *tile = lv_obj_get_parent(grid);
      show_error_popup(tile, "Cannot activate 24V MODE while MOTOR is ON");
    }
    return false;
  }
  if (self->isToggled() && inverter_btn && inverter_btn->isToggled()) {
    Serial.println("ERROR: Cannot deactivate 24V MODE while INVERTER is ON");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    if (grid) {
      lv_obj_t *tile = lv_obj_get_parent(grid);
      show_error_popup(tile, "Cannot deactivate 24V MODE while INVERTER is ON");
    }
    return false;
  }
  return true;
}

bool validate_motor(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  if (self && !self->isToggled() && btn24v && btn24v->isToggled()) {
    Serial.println("ERROR: Cannot activate MOTOR while 24V MODE is ON");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    if (grid) {
      lv_obj_t *tile = lv_obj_get_parent(grid);
      show_error_popup(tile, "Cannot activate MOTOR while 24V MODE is ON");
    }
    return false;
  }
  return true;
}

bool validate_inverter(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  if (self && !self->isToggled() && btn24v && !btn24v->isToggled()) {
    Serial.println("ERROR: Cannot activate INVERTER while 24V MODE is OFF");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    if (grid) {
      lv_obj_t *tile = lv_obj_get_parent(grid);
      show_error_popup(tile, "Cannot activate INVERTER while 24V MODE is OFF");
    }
    return false;
  }
  return true;
}

bool validate_voice_mode(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  return !(self && self->isToggled());
}
