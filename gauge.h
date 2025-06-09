#ifndef GAUGE_H
#define GAUGE_H

#include <lvgl.h>
#include "colors.h"
#include "config.h"

class Gauge {
  lv_obj_t *container;
  lv_obj_t *bars[GAUGE_SEG_COUNT];
  lv_obj_t *label;

  static const lv_color_t dark_colors[GAUGE_SEG_COUNT];
  static const lv_color_t lit_colors[GAUGE_SEG_COUNT];

public:
  Gauge(lv_obj_t *parent, const char *text);
  lv_obj_t *getContainer() const { return container; }
  void setLevel(float level); // level normalized 0..1
};

#endif
