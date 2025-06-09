#ifndef GAUGE_TILE_H
#define GAUGE_TILE_H

#include "gauge.h"
#include <lvgl.h>

class GaugeTile {
  lv_obj_t *tile;
  Gauge *gauges[6];

public:
  GaugeTile(lv_obj_t *tileview, int row_id);
  lv_obj_t *getTile() const { return tile; }
  Gauge *getGauge(int idx) const { return (idx >= 0 && idx < 6) ? gauges[idx] : nullptr; }
  ~GaugeTile();
};

#endif
