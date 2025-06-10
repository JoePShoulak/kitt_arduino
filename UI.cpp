#include "UI.h"

#include "button_panel.h"
#include "colors.h"
#include "config.h"
#include "voice_synth.h"
#include "voice_tile.h"
#include "gauge_tile.h"
#include "gauge_anim.h"

UI ui;

// Global UI element pointers defined here
VoiceTile *voiceTile = nullptr;
GaugeTile *gaugeTile = nullptr;
GaugeTile *leftGaugeTile = nullptr;
Button *motor_btn = nullptr;
Button *btn24v = nullptr;
Button *inverter_btn = nullptr;

void UI::init() {
  canvas = lv_scr_act();
  lv_obj_set_style_bg_color(canvas, BLACK, 0);

  tiles = lv_tileview_create(canvas);
  lv_obj_set_style_bg_color(tiles, BLACK, 0);
  lv_obj_set_scrollbar_mode(tiles, LV_SCROLLBAR_MODE_OFF);

  static const char *const left_labels[] = {"RPM", "MOTOR CURRENT",
                                            "PERIPHERAL CURRENT"};
  leftGaugeTile = new GaugeTile(tiles, 0, left_labels, 3, true);
  ::leftGaugeTile = leftGaugeTile;

  leftPanel = ButtonPanel::createTile(tiles, 1, button_panel1);
  voiceTile = new VoiceTile(tiles, 2, voice_buttons);
  ::voiceTile = voiceTile;
  for (int i = 0; i < 3; ++i) {
    Button *btn = voiceTile->getButton(i);
    if (btn)
      btn->setCallback(voice_mode_cb);
  }
  rightPanel = ButtonPanel::createTile(tiles, 3, button_panel2);

  static const char *const right_labels[] = {"BATTERY VOLTAGE",
                                             "BATTERY CURRENT",
                                             "SOLAR VOLTAGE",
                                             "SOLAR CURRENT",
                                             "TEMPERATURE"};
  gaugeTile = new GaugeTile(tiles, 4, right_labels, 5);
  ::gaugeTile = gaugeTile;
  motor_btn = rightPanel->getButton(0);
  if (motor_btn) {
    motor_btn->setCallback(motor_override_cb);
    motor_btn->setValidate(validate_motor);
  }
  btn24v = rightPanel->getButton(2);
  if (btn24v) {
    btn24v->setValidate(validate_24v);
  }
  inverter_btn = rightPanel->getButton(3);
  if (inverter_btn) {
    inverter_btn->setValidate(validate_inverter);
  }

  lv_obj_set_tile_id(tiles, 2, 0, LV_ANIM_OFF); // start on voice tile

  voice_anim_timer = lv_timer_create(voice_anim_cb, 50, nullptr);
  gauge_anim_timer = lv_timer_create(gauge_anim_cb, 50, nullptr);
}
