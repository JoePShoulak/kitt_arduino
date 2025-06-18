#ifndef UI_H
#define UI_H

#include <lvgl.h>
#include <GigaAudio.h>

class ButtonTile;
class VoiceTile;
class GaugeTile;
class GigaAudio;

class UI
{
  lv_obj_t *canvas = nullptr;
  lv_obj_t *tiles = nullptr;

  GaugeTile *leftGaugeTile = nullptr;
  GaugeTile *rightGaugeTile = nullptr;
  ButtonTile *leftPanel = nullptr;
  ButtonTile *rightPanel = nullptr;
  VoiceTile *voiceTile = nullptr;

  lv_timer_t *voice_anim_timer = nullptr;
  lv_timer_t *gauge_anim_timer = nullptr;

public:
  void init(GigaAudio &audio);

  VoiceTile *getVoiceTile() const { return voiceTile; }
  ButtonTile *getLeftPanel() const { return leftPanel; }
  ButtonTile *getRightPanel() const { return rightPanel; }
  GaugeTile *getLeftGaugeTile() const { return leftGaugeTile; }
  GaugeTile *getRightGaugeTile() const { return rightGaugeTile; }
};

extern UI ui;

#endif
