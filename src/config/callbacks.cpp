#include <Arduino.h>
#include <button.h>
#include <popup.h>
#include "../tiles/voice_tile.h"
#include "../helpers/audio_helper.h"
#include "globals.h"
#include "callbacks.h"

lv_obj_t *blackout_overlay = nullptr;
static bool blackout_first_release = false;

// ==== HELPERS ====

static void toggle_sound(Button *self, const char *on_clip, const char *off_clip)
{
  audio_play(self->isToggled() ? on_clip : off_clip);
}

// ==== Left button panel ====
void turbo_boost_btn_cb(lv_event_t *e) { audio_play("turbo_boost.wav"); }
void theme_btn_cb(lv_event_t *e) { audio_play("theme.wav"); }
void intro_btn_cb(lv_event_t *e) { audio_play("intro.wav"); }
void explode_btn_cb(lv_event_t *e) { audio_play("explode.wav"); }
void joseph_btn_cb(lv_event_t *e) { audio_play("joseph.wav"); }
void shoe_btn_cb(lv_event_t *e) { audio_play("shoe.wav"); }
void michelle_btn_cb(lv_event_t *e) { audio_play("michelle.wav"); }
void shawn_btn_cb(lv_event_t *e) { audio_play("shawn.wav"); }

void motor_override_cb(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "motor_on.wav", "motor_off.wav");
}

void evade_btn_cb(lv_event_t *e)
{
  audio_play("evade_on.wav");

  backlight.set(0);
  blackout_first_release = false;
  blackout_overlay = show_fullscreen_popup(nullptr);
  lv_obj_add_event_cb(blackout_overlay, blackout_overlay_cb, LV_EVENT_ALL, nullptr);
}

void gps_btn_cb(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "gps_on.wav", "gps_off.wav");
}

void radio_btn_cb(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "radio_on.wav", "radio_off.wav");
}

void usb_btn_cb(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "usb_on.wav", "usb_off.wav");
}

void lighting_btn_cb(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "lighting_on.wav", "lighting_off.wav");
}

void btn48v_cb(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "24V_off.wav", "24v_on.wav");
}

void inverter_btn_cb(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));
  toggle_sound(self, "inverter_on.wav", "inverter_off.wav");
}

// ==== Voice panel ====
void auto_cruise_btn_cb(lv_event_t *e)
{
  audio_play("auto_cruise.wav");
  cruise_mode_cb(e);
}

void normal_cruise_btn_cb(lv_event_t *e)
{
  audio_play("normal_cruise.wav");
  cruise_mode_cb(e);
}

void pursuit_btn_cb(lv_event_t *e)
{
  audio_play("pursuit.wav");
  cruise_mode_cb(e);
}

void cruise_mode_cb(lv_event_t *e)
{
  auto self = static_cast<Button *>(lv_event_get_user_data(e));

  if (!self->isToggled())
    return;

  for (int i = 0; i < 3; ++i)
  {
    Button *other = voiceTile->getButton(i);

    if (other != self && other->isToggled())
      other->handlePress();
  }
}

// Misc
void blackout_overlay_cb(lv_event_t *e)
{
  if (lv_event_get_code(e) == LV_EVENT_RELEASED && !blackout_first_release)
  {
    blackout_first_release = true;
  }
  else if (blackout_first_release)
  {
    lv_obj_del(blackout_overlay);
    blackout_overlay = nullptr;
    backlight.set(255);
    blackout_first_release = false;
  }
}
