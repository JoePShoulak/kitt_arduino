// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <lvgl.h>

#include "button.h"
#include "button_panel.h"
#include "config.h"
#include "voice_scene.h"
#include "audio_manager.h"

GigaDisplay_GFX tft; // Init tft
Arduino_GigaDisplayTouch TouchDetector;

void make_panel(ButtonData const* config, lv_obj_t* tileview, int row_id) {
    auto* tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
    lv_obj_set_style_bg_color(tile, BLACK, 0);

    new ButtonPanel(tile, config);
}

ButtonData const voice_buttons[3] = {
    { "AUTO CRUISE", null_btn, true, 1000 },
    { "NORMAL CRUISE", null_btn, true, 1000 },
    { "PURSUIT", null_btn, true, 1000 },
};

void setup() {
  Serial.begin(115200); // Initialize Serial
  lv_init(); // Initialize LVGL
  tft.begin(); // Initialize Giga Display
  TouchDetector.begin();
  AudioManager::instance().begin("/USB DISK/AUDIO");

  auto* canvas = lv_scr_act();
  lv_obj_set_style_bg_color(canvas, BLACK, 0);
  
  auto* tiles = lv_tileview_create(canvas);
  lv_obj_set_style_bg_color(tiles, BLACK, 0);
  lv_obj_set_scrollbar_mode(tiles, LV_SCROLLBAR_MODE_OFF);

  make_panel(button_panel1, tiles, 0);
  lv_obj_t* voice_tile = create_voice_tile(tiles, 1, voice_buttons);
  make_panel(button_panel2, tiles, 2);

  lv_obj_set_tile_id(tiles, 1, 0, LV_ANIM_OFF); // start on voice tile
  LV_UNUSED(voice_tile); 
}

void loop() {
  lv_timer_handler();
  AudioManager::instance().update();
  delay(5);
}

