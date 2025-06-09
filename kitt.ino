// kitt.ino

#include "audio_helper.h"
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay_GFX.h>
#include <lvgl.h>

#include "button.h"
#include "button_panel.h"
#include "config.h"
#include "popup.h"
#include "voice_tile.h"

GigaDisplay_GFX tft; // Init tft
Arduino_GigaDisplayTouch TouchDetector;
VoiceTile *voiceTile = nullptr;
Button *motor_btn = nullptr;
Button *btn24v = nullptr;
Button *inverter_btn = nullptr;

void setup() {
  Serial.begin(115200); // Initialize Serial
  lv_init();            // Initialize LVGL
  tft.begin();          // Initialize Giga Display
  TouchDetector.begin();

  auto *canvas = lv_scr_act();
  lv_obj_set_style_bg_color(canvas, BLACK, 0);

  auto *tiles = lv_tileview_create(canvas);
  lv_obj_set_style_bg_color(tiles, BLACK, 0);
  lv_obj_set_scrollbar_mode(tiles, LV_SCROLLBAR_MODE_OFF);

  auto leftPanel = ButtonPanel::createTile(tiles, 0, button_panel1);
  voiceTile = new VoiceTile(tiles, 1, voice_buttons);
  for (int i = 0; i < 3; ++i) {
    Button *btn = voiceTile->getButton(i);
    if (btn)
      btn->setCallback(voice_mode_cb);
  }
  auto rightPanel = ButtonPanel::createTile(tiles, 2, button_panel2);
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

  lv_obj_set_tile_id(tiles, 1, 0, LV_ANIM_OFF); // start on voice tile

  // audio_setup();
}

void loop() {
  lv_timer_handler();
  // audio_loop();
}
