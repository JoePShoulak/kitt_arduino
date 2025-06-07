// kitt.ino

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <lvgl.h>

#include "buttons.h"
#include "button_panel.h"
#include "config.h"

GigaDisplay_GFX tft; // Init tft
Arduino_GigaDisplayTouch  TouchDetector;

void setup() {
  Serial.begin(115200); // Initialize Serial
  lv_init(); // Initialize LVGL
  tft.begin(); // Initialize Giga Display
  TouchDetector.begin();
  
  auto* tiles = lv_tileview_create(lv_scr_act());
  for (int i = 0; i < 2; ++i) {
    auto* tile = lv_tileview_add_tile(tiles, i, 0, LV_DIR_RIGHT);
    new ButtonPanel(tile, button_data);
  }
}

void loop() {
  lv_timer_handler();
  delay(5);
}
