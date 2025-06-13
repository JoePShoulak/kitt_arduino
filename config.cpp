#include <Arduino.h> // for Serial

#include <button.h>
#include "config.h"
#include <popup.h>
#include <voice_tile.h>
#include "audio_helper.h"

// This file implements the callbacks and validation logic declared in
// config.h. Functions are grouped by purpose for clarity.

lv_obj_t *blackout_overlay = nullptr;
static bool blackout_first_release = false;
static bool blackout_pressed_after = false;

void aud_indicator_cb(lv_event_t *e) {
  if (!e)
    return;
  lv_event_code_t code = lv_event_get_code(e);
  if (code != LV_EVENT_PRESSED)
    return;
  audio_stop();
}

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
  audio_play("intro.wav");
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

void michelle_btn_cb(lv_event_t *e) {
  Serial.println("MICHELLE clip requested");
  audio_play("michelle.wav");
}

void shawn_btn_cb(lv_event_t *e) {
  Serial.println("SHAWN clip requested");
  audio_play("shawn.wav");
}

void theme_btn_cb(lv_event_t *e) {
  Serial.println("THEME clip requested");
  audio_play("theme.wav");
}

void turbo_boost_btn_cb(lv_event_t *e) {
  Serial.println("TURBO BOOST clip requested");
  audio_play("turbo_boost.wav");
}

void auto_cruise_btn_cb(lv_event_t *e) {
  Serial.println("AUTO CRUISE clip requested");
  audio_play("auto_cruise.wav");
  voice_mode_cb(e);
}

void normal_cruise_btn_cb(lv_event_t *e) {
  Serial.println("NORMAL CRUISE clip requested");
  audio_play("normal_cruise.wav");
  voice_mode_cb(e);
}

void pursuit_btn_cb(lv_event_t *e) {
  Serial.println("PURSUIT clip requested");
  audio_play("pursuit.wav");
  voice_mode_cb(e);
}

// Triggered when the EVADE button is pressed; simply play the audio clip.
void evade_btn_cb(lv_event_t *e) {
  Serial.println("EVADE clip requested");
  audio_play("evade_on.wav");
  blackout_cb(e);
}

static void toggle_sound(Button *self, const char *on_clip, const char *off_clip) {
  if (!self)
    return;
  audio_play(self->isToggled() ? on_clip : off_clip);
}

void gps_btn_cb(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "gps_on.wav", "gps_off.wav");
}

void radio_btn_cb(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "radio_on.wav", "radio_off.wav");
}

void usb_btn_cb(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "usb_on.wav", "usb_off.wav");
}

void lighting_btn_cb(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "lighting_on.wav", "lighting_off.wav");
}

void btn48v_cb(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "24V_on.wav", "24v_off.wav");
}

void inverter_btn_cb(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "inverter_on.wav", "inverter_off.wav");
}

void motor_override_cb(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  Serial.println("MOTOR clip requested");
  toggle_sound(self, "motor_on.wav", "motor_off.wav");
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
bool validate_48v(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  if (!self)
    return true;
  if (self->isToggled() && motor_btn && motor_btn->isToggled()) {
    Serial.println("ERROR: Cannot deactivate 48V MODE while MOTOR is ON");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    if (grid) {
      lv_obj_t *tile = lv_obj_get_parent(grid);
      show_error_popup(tile, "Cannot deactivate 48V MODE while MOTOR is ON");
    }
    return false;
  }
  if (!self->isToggled() && inverter_btn && inverter_btn->isToggled()) {
    Serial.println("ERROR: Cannot activate 48V MODE while INVERTER is ON");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    if (grid) {
      lv_obj_t *tile = lv_obj_get_parent(grid);
      show_error_popup(tile, "Cannot activate 48V MODE while INVERTER is ON");
    }
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
    return false;
  }
  return true;
}

bool validate_inverter(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  if (self && !self->isToggled() && btn48v && btn48v->isToggled()) {
    Serial.println("ERROR: Cannot activate INVERTER while 48V MODE is ON");
    lv_obj_t *grid = lv_obj_get_parent(self->getLVButton());
    if (grid) {
      lv_obj_t *tile = lv_obj_get_parent(grid);
      show_error_popup(tile, "Cannot activate INVERTER while 48V MODE is ON");
    }
    return false;
  }
  return true;
}

bool validate_voice_mode(lv_event_t *e) {
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  return !(self && self->isToggled());
}
