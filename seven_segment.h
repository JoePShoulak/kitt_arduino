#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include <lvgl.h>

class SevenSegmentDisplay {
  lv_obj_t *container;
  lv_obj_t *segments[3][7];

  void createDigit(int idx);

public:
  SevenSegmentDisplay(lv_obj_t *parent);
  void setValue(int value);
  lv_obj_t *getObj() const { return container; }
};

#endif
