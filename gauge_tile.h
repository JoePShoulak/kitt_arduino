#ifndef GAUGE_TILE_H
#define GAUGE_TILE_H

#include "gauge.h"
#include <lvgl.h>

class GaugeTile {
  lv_obj_t *tile;
  Gauge *gauge;

public:
  GaugeTile(lv_obj_t *tileview, int row_id, const char *label);
  ~GaugeTile();

  Gauge *getGauge() const { return gauge; }
  lv_obj_t *getTile() const { return tile; }
};

#endif
