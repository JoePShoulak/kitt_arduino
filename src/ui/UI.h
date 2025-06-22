#ifndef UI_H
#define UI_H

#include <lvgl.h>
#include <GigaAudio.h>
#include <Arduino_GigaDisplay.h>

#include "tiles/button_tile.h"
#include "tiles/voice_tile.h"
#include "tiles/gauge_tile.h"

class GigaAudio;

class UI
{
  lv_obj_t *canvas = nullptr;
  lv_obj_t *tiles = nullptr;

  lv_timer_t *gauge_anim_timer = nullptr;

public:
  GaugeTile *leftGaugeTile;
  GaugeTile *rightGaugeTile;
  ButtonTile *leftButtonTile = nullptr;
  ButtonTile *rightButtonTile = nullptr;
  VoiceTile *voiceTile;
  lv_obj_t *blackout_overlay;
  GigaDisplayBacklight backlight;

  bool init();
};

extern UI ui;

#endif
