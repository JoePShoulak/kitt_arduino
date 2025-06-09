#ifndef UI_H
#define UI_H

#include <lvgl.h>

class ButtonPanel;
class VoiceTile;

class UI {
  lv_obj_t *canvas = nullptr;
  lv_obj_t *tiles = nullptr;
  ButtonPanel *leftPanel = nullptr;
  VoiceTile *voiceTile = nullptr;
  ButtonPanel *rightPanel = nullptr;
  lv_timer_t *voice_anim_timer = nullptr;

public:
  void init();
  VoiceTile *getVoiceTile() const { return voiceTile; }
  ButtonPanel *getLeftPanel() const { return leftPanel; }
  ButtonPanel *getRightPanel() const { return rightPanel; }
};

extern UI ui;

#endif
