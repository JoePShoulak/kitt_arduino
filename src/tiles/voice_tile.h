#ifndef VOICE_TILE_H
#define VOICE_TILE_H

#include <lvgl.h>
#include <voice_visualiser.h>
#include <button.h>
#include <indicator.h>

class GigaAudio;

class VoiceTile
{
  lv_obj_t *tile;
  lv_obj_t *grid;

public:
  VoiceVisualiser *visualiser;
  Indicator *indicators[8];
  Button *buttons[3];

  VoiceTile(lv_obj_t *tileview, int row_id, ButtonData const *button_data);
  ~VoiceTile();

  lv_obj_t *getTile() const { return tile; }
  lv_obj_t *getGrid() const { return grid; }
};

#endif
