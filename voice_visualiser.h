#ifndef VOICE_VISUALIZER_H
#define VOICE_VISUALIZER_H

#include <lvgl.h>

class VoiceVisualiser {
  lv_obj_t *viz;
  lv_obj_t *cols[3];
  int col_count[3];

  void make_column(int id, int count);

public:
  VoiceVisualiser(lv_obj_t *parent);
  void set_cols_active(float ratio_norm);
};

#endif
