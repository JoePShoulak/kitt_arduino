// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <lvgl.h>

#include "buttons.h"
#include "button_panel.h"
#include "config.h"
#include "audio_manager.h"

GigaDisplay_GFX tft; // Init tft
Arduino_GigaDisplayTouch TouchDetector;

static lv_obj_t *voice_bars[4];

static void create_voice_visualizer(lv_obj_t *parent) {
  int spacing = 10;
  int width = 30;
  for (int i = 0; i < 4; ++i) {
    voice_bars[i] = lv_obj_create(parent);
    lv_obj_set_size(voice_bars[i], width, 10);
    lv_obj_set_style_radius(voice_bars[i], 5, 0);
    lv_obj_set_style_border_width(voice_bars[i], 0, 0);
    lv_obj_set_style_bg_color(voice_bars[i], GREEN, 0);
    lv_obj_align(voice_bars[i], LV_ALIGN_BOTTOM_MID, (i - 1.5) * (width + spacing), -20);
  }
}

static void update_voice_visualizer(float level) {
  if (level < 0) level = 0;
  if (level > 1) level = 1;
  int max_height = 60;
  int h = 10 + (int)(level * max_height);
  for (int i = 0; i < 4; ++i) {
    lv_obj_set_height(voice_bars[i], h);
  }
}

void make_panel(ButtonData const* config, lv_obj_t* tileview, int row_id) {
    auto* tile = lv_tileview_add_tile(tileview, row_id, 0, LV_DIR_HOR);
    lv_obj_set_style_bg_color(tile, BLACK, 0);

    new ButtonPanel(tile, config);
}

void setup() {
  Serial.begin(115200); // Initialize Serial
  lv_init(); // Initialize LVGL
  tft.begin(); // Initialize Giga Display
  TouchDetector.begin();
  audioSetup();
  audioPlay("explode.mp3");

  auto* canvas = lv_scr_act();
  lv_obj_set_style_bg_color(canvas, BLACK, 0);

  create_voice_visualizer(canvas);

  auto* tiles = lv_tileview_create(canvas);
  lv_obj_set_style_bg_color(tiles, BLACK, 0);
  lv_obj_set_scrollbar_mode(tiles, LV_SCROLLBAR_MODE_OFF);

  make_panel(button_panel1, tiles, 0);
  make_panel(button_panel2, tiles, 1);
}

void loop() {
  lv_timer_handler();
  audioUpdate();
  update_voice_visualizer(audioLevel());
  delay(5);
}
