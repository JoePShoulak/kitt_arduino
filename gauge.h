#ifndef GAUGE_H
#define GAUGE_H

#include <lvgl.h>
#include "colors.h"

class Gauge {
  lv_obj_t *container;        // outer container
  lv_obj_t *segments[10];     // gauge segments
  lv_obj_t *label_obj;

  static lv_color_t get_dark_color(int idx);
  static lv_color_t get_light_color(int idx);

public:
  Gauge(lv_obj_t *parent, const char *label);
  void setLevel(float level); // 0..1
  lv_obj_t *getContainer() const { return container; }
};

#endif
