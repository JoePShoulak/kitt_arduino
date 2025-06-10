#ifndef GAUGE_TILE_H
#define GAUGE_TILE_H

#include <lvgl.h>

class Gauge;

class GaugeTile {
  lv_obj_t *tile;
  Gauge **gauges;
  int gauge_count;

public:
  GaugeTile(lv_obj_t *tileview, int row_id, const char *const *labels,
            int count);
  ~GaugeTile();
  Gauge *getGauge(int idx) const;
  lv_obj_t *getTile() const { return tile; }
};

#endif
