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
  VoiceVisualiser *visualiser;
  Indicator *indicators[8];
  Button *buttons[3];

public:
  VoiceTile(lv_obj_t *tileview, int row_id, ButtonData const *button_data, GigaAudio *audio);
  ~VoiceTile();

  lv_obj_t *getTile() const { return tile; }
  VoiceVisualiser *getVisualiser() const { return visualiser; }
  Indicator *getIndicator(int index) const { return (index >= 0 && index < 8) ? indicators[index] : nullptr; }
  Button *getButton(int index) const { return (index >= 0 && index < 3) ? buttons[index] : nullptr; }
  lv_obj_t *getGrid() const { return grid; }
};

#endif
