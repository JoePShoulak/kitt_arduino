#include <Arduino.h> // for Serial

#include "button.h"
#include "config.h"
#include "popup.h"
#include "voice_tile.h"
#include "audio_helper.h"

// This file implements the callbacks and validation logic declared in
// config.h. Functions are grouped by purpose for clarity.

lv_obj_t *blackout_overlay = nullptr;
static bool blackout_first_release = false;
static bool blackout_pressed_after = false;

static void blackout_overlay_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_PRESSED) {
    if (blackout_first_release)
      blackout_pressed_after = true;
    return;
  }

  if (code != LV_EVENT_RELEASED)
    return;

  if (!blackout_first_release) {
    blackout_first_release = true;
    return;
  }

  if (!blackout_pressed_after)
    return;

  if (blackout_overlay) {
    lv_obj_del(blackout_overlay);
    blackout_overlay = nullptr;
  }
  blackout = false;
  backlight.set(255);
  blackout_first_release = false;
  blackout_pressed_after = false;
  if (blackout_btn && blackout_btn->isToggled()) {
    blackout_btn->handlePress();
  }
}

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

void intro_btn_cb(lv_event_t *e) {
  Serial.println("INTRO clip requested");
  audio_setup();
}

void explode_btn_cb(lv_event_t *e) {
  Serial.println("EXPLODE clip requested");
  audio_play("explode.wav");
}

void joseph_btn_cb(lv_event_t *e) {
  Serial.println("JOSEPH clip requested");
  audio_play("joseph.wav");
}

void shoe_btn_cb(lv_event_t *e) {
  Serial.println("SHOE clip requested");
  audio_play("shoe.wav");
}

void motor_override_cb(lv_event_t *e) {
  Serial.println("MOTOR override callback!");
}

void blackout_cb(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  if (!self)
    return;
  if (self->isToggled()) {
    Serial.println("BLACKOUT engaged");
    blackout = true;
    backlight.set(0); // turn off backlight
    blackout_first_release = false;
    blackout_pressed_after = false;
    if (!blackout_overlay) {
      blackout_overlay = show_fullscreen_popup(nullptr);
      lv_obj_add_event_cb(blackout_overlay, blackout_overlay_cb,
                          LV_EVENT_ALL, nullptr);
    }
  } else {
    Serial.println("BLACKOUT disengaged");
    blackout = false;
    backlight.set(255); // restore brightness
    blackout_first_release = false;
    blackout_pressed_after = false;
    if (blackout_overlay) {
      lv_obj_del(blackout_overlay);
      blackout_overlay = nullptr;
    }
  }
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
