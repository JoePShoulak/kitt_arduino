#ifndef INDICATOR_H
#define INDICATOR_H

#include <lvgl.h>

struct IndicatorData {
  const char *label;
  lv_color_t dark;
  lv_color_t light;
};

class Indicator {
  const IndicatorData &data;
  lv_obj_t *indicator;

  void set_style(lv_obj_t *obj);

public:
  Indicator(const IndicatorData &data, lv_obj_t *parent);
  void toggle(bool on);
};

#endif
