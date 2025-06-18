#include "UI.h"

#include <colors.h>
#include "button_tile.h"
#include "animations.h"
#include "voice_tile.h"
#include "gauge_tile.h"
#include "validators.h"

UI ui;

// Global UI element pointers defined here
VoiceTile *voiceTile = nullptr;
GaugeTile *rightGaugeTile = nullptr;
GaugeTile *leftGaugeTile = nullptr;
Button *motor_btn = nullptr;
Button *blackout_btn = nullptr;
Button *btn48v = nullptr;
Button *inverter_btn = nullptr;

void UI::init(GigaAudio &audio)
{
  Serial.print("Initializing UI...");

  canvas = lv_scr_act();
  lv_obj_set_style_bg_color(canvas, BLACK, 0);

  tiles = lv_tileview_create(canvas);
  lv_obj_set_style_bg_color(tiles, BLACK, 0);
  lv_obj_set_scrollbar_mode(tiles, LV_SCROLLBAR_MODE_OFF);

  leftGaugeTile = new GaugeTile(tiles, 0, left_labels, 3, true);
  rightGaugeTile = new GaugeTile(tiles, 4, right_labels, 5);
  ::leftGaugeTile = leftGaugeTile;
  ::rightGaugeTile = rightGaugeTile;

  voiceTile = new VoiceTile(tiles, 2, voice_buttons, &audio);
  ::voiceTile = voiceTile;

  leftPanel = ButtonTile::createTile(tiles, 1, button_tile1);
  rightPanel = ButtonTile::createTile(tiles, 3, button_tile2);

  // Provide global access for validation callbacks
  motor_btn = rightPanel->getButton(0);
  blackout_btn = rightPanel->getButton(1);
  btn48v = rightPanel->getButton(2);
  inverter_btn = rightPanel->getButton(3);

  lv_obj_set_tile_id(tiles, 2, 0, LV_ANIM_OFF); // start on voice tile

  voice_anim_timer = lv_timer_create(voice_anim_cb, 50, &audio);
  gauge_anim_timer = lv_timer_create(gauge_anim_cb, 150, nullptr);

  Serial.println(" done!");
}
