#ifndef VOICE_VISUALIZER_H
#define VOICE_VISUALIZER_H

#include "lvgl_wrapper.h"

class VoiceVisualiser {
  lv_obj_t *viz;
  lv_obj_t *cols[3];
  int col_count[3];

  lv_timer_t *timer = nullptr;
  float level = 0.f; // normalised 0..1 value
  bool fading = false;
  uint32_t last_update = 0; // lv_tick timestamp of last level update

  void make_column(int id, int count);
  static void timer_cb(lv_timer_t *t);

public:
  VoiceVisualiser(lv_obj_t *parent);
  void set_cols_active(float ratio_norm);
  void setLevel(float lvl);
  void startFade();
  lv_obj_t *getObject() const { return viz; }
};

#endif
