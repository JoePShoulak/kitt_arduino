#ifndef GAUGE_TILE_H
#define GAUGE_TILE_H

#include <lvgl.h>

class Gauge;

class GaugeTile {
  lv_obj_t *tile;
  Gauge *battery;
  Gauge *voltage;
  Gauge *current;
  Gauge *temperature;

public:
  GaugeTile(lv_obj_t *tileview, int row_id);
  ~GaugeTile();
  Gauge *getBattery() const { return battery; }
  Gauge *getVoltage() const { return voltage; }
  Gauge *getCurrent() const { return current; }
  Gauge *getTemperature() const { return temperature; }
  lv_obj_t *getTile() const { return tile; }
};

#endif
