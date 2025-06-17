#include <Arduino.h>
#include <button.h>
#include "config.h"
#include <popup.h>
#include "audio_helper.h"
#include "validators.h"

bool validate_48v(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  if (!self)
    return true;
  if (self->isToggled() && motor_btn && motor_btn->isToggled()) {
    Serial.println("ERROR: Cannot deactivate 48V MODE while MOTOR is ON");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    if (grid) {
      lv_obj_t *tile = lv_obj_get_parent(grid);
      show_error_popup(tile,
                       "Cannot deactivate 48V MODE while MOTOR is ON");
    }
    audio_play("error.wav");
    return false;
  }
  if (!self->isToggled() && inverter_btn && inverter_btn->isToggled()) {
    Serial.println("ERROR: Cannot activate 48V MODE while INVERTER is ON");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    if (grid) {
      lv_obj_t *tile = lv_obj_get_parent(grid);
      show_error_popup(tile,
                       "Cannot activate 48V MODE while INVERTER is ON");
    }
    audio_play("error.wav");
    return false;
  }
  return true;
}

bool validate_motor(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  if (self && !self->isToggled() && btn48v && !btn48v->isToggled()) {
    Serial.println("ERROR: Cannot activate MOTOR while 48V MODE is OFF");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    if (grid) {
      lv_obj_t *tile = lv_obj_get_parent(grid);
      show_error_popup(tile, "Cannot activate MOTOR while 48V MODE is OFF");
    }
    audio_play("error.wav");
    return false;
  }
  return true;
}

bool validate_inverter(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  if (self && !self->isToggled() && btn48v && btn48v->isToggled()) {
    Serial.println(
        "ERROR: Cannot activate INVERTER while 48V MODE is ON");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    if (grid) {
      lv_obj_t *tile = lv_obj_get_parent(grid);
      show_error_popup(tile,
                       "Cannot activate INVERTER while 48V MODE is ON");
    }
    audio_play("error.wav");
    return false;
  }
  return true;
}

bool validate_voice_mode(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  if (self && self->isToggled()) {
    audio_play("error.wav");
    return false;
  }
  return true;
}

