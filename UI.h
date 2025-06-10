#ifndef UI_H
#define UI_H

#include "lvgl_wrapper.h"

class ButtonPanel;
class VoiceTile;
class GaugeTile;

class UI {
  lv_obj_t *canvas = nullptr;
  lv_obj_t *tiles = nullptr;
  GaugeTile *leftGaugeTile = nullptr;
  ButtonPanel *leftPanel = nullptr;
  VoiceTile *voiceTile = nullptr;
  ButtonPanel *rightPanel = nullptr;
  GaugeTile *gaugeTile = nullptr;
  lv_timer_t *voice_anim_timer = nullptr;

public:
  void init();
  VoiceTile *getVoiceTile() const { return voiceTile; }
  ButtonPanel *getLeftPanel() const { return leftPanel; }
  ButtonPanel *getRightPanel() const { return rightPanel; }
  GaugeTile *getGaugeTile() const { return gaugeTile; }
  GaugeTile *getLeftGaugeTile() const { return leftGaugeTile; }
};

extern UI ui;

#endif
