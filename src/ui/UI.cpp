#include "UI.h"

#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay.h>
#include <colors.h>
#include "../misc/animations.h"

UI ui;
GigaDisplay_GFX tft;
Arduino_GigaDisplayTouch TouchDetector;

bool UI::init()
{
  lv_init();         // Initialize LVGL (void)
  tft.begin();       // Initialize Giga Display (void)
  backlight.begin(); // Initialize backlight reference (void)

  if (!TouchDetector.begin())
  {
    Serial.println("❌Failed to initialize Touch Detector");
    return false;
  }

  canvas = lv_scr_act();
  lv_obj_set_style_bg_color(canvas, BLACK, 0);

  tiles = lv_tileview_create(canvas);
  lv_obj_set_style_bg_color(tiles, BLACK, 0);
  lv_obj_set_scrollbar_mode(tiles, LV_SCROLLBAR_MODE_OFF);

  leftButtonTile = new ButtonTile(tiles, 1, left_buttons);
  leftGaugeTile = new GaugeTile(tiles, 0, left_gauges, 3, true);
  voiceTile = new VoiceTile(tiles, 2, voice_buttons);
  rightButtonTile = new ButtonTile(tiles, 3, right_buttons);
  rightGaugeTile = new GaugeTile(tiles, 4, right_gauges, 5);

  lv_obj_set_tile_id(tiles, 2, 0, LV_ANIM_OFF); // start on voice tile
  lv_timer_create(gauge_anim_cb, 150, nullptr);

  return true;
}
