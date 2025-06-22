#include "UI.h"

#include <colors.h>

#include "misc/animations.h"

UI ui;

void UI::init(GigaAudio &audio)
{
  Serial.print("Initializing UI...");
  lv_init(); // Initialize LVGL

  canvas = lv_scr_act();
  lv_obj_set_style_bg_color(canvas, BLACK, 0);

  tiles = lv_tileview_create(canvas);
  lv_obj_set_style_bg_color(tiles, BLACK, 0);
  lv_obj_set_scrollbar_mode(tiles, LV_SCROLLBAR_MODE_OFF);

  leftGaugeTile = new GaugeTile(tiles, 0, left_gauges, 3, true);
  rightGaugeTile = new GaugeTile(tiles, 4, right_gauges, 5);

  voiceTile = new VoiceTile(tiles, 2, voice_buttons, &audio);

  leftButtonTile = ButtonTile::createTile(tiles, 1, button_tile1);
  rightButtonTile = ButtonTile::createTile(tiles, 3, button_tile2);

  backlight.begin();

  lv_obj_set_tile_id(tiles, 2, 0, LV_ANIM_OFF); // start on voice tile

  voice_anim_timer = lv_timer_create(voice_anim_cb, 50, &audio);
  gauge_anim_timer = lv_timer_create(gauge_anim_cb, 150, nullptr);

  Serial.println(" done!");
}
