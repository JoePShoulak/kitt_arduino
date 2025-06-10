#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include "lvgl_wrapper.h"

class SevenSegmentDisplay {
  lv_obj_t *container;
  lv_obj_t *segments[3][7];
  lv_obj_t *label;

  void createDigit(lv_obj_t *parent, int idx);

public:
  SevenSegmentDisplay(lv_obj_t *parent, const char *labelText = "MPH");
  void setValue(int value);
  lv_obj_t *getObj() const { return container; }
};

#endif
