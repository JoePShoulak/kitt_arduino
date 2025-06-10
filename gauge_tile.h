#ifndef GAUGE_TILE_H
#define GAUGE_TILE_H

#include <lvgl.h>

class Gauge;

class GaugeTile {
  lv_obj_t *tile;
  Gauge *voltage;
  Gauge *current;

public:
  GaugeTile(lv_obj_t *tileview, int row_id);
  ~GaugeTile();
  Gauge *getVoltage() const { return voltage; }
  Gauge *getCurrent() const { return current; }
  lv_obj_t *getTile() const { return tile; }
};

#endif
