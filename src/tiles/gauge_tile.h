#ifndef GAUGE_TILE_H
#define GAUGE_TILE_H

#include <lvgl.h>
#include <gauge.h>

class Gauge;
class SevenSegmentDisplay;

class GaugeTile
{
  lv_obj_t *tile;
  Gauge **gauges;
  int gauge_count;
  SevenSegmentDisplay *display;

public:
  GaugeTile(lv_obj_t *tileview, int row_id, GaugeData const *data, int count, bool with_display = false);
  ~GaugeTile();
  Gauge *getGauge(int idx) const;
  SevenSegmentDisplay *getSevenSegmentDisplay() const { return display; }
  lv_obj_t *getTile() const { return tile; }
};

#endif
