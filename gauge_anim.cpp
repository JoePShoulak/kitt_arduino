#include "gauge_anim.h"
#include "config.h"
#include "gauge_tile.h"
#include "gauge.h"
#include "seven_segment.h"
#include <stdlib.h>

// Update gauges and the speedometer using a simple random walk.
void gauge_anim_cb(lv_timer_t *t) {
  (void)t;

  static int left_vals[3] = {0};
  static int right_vals[5] = {0};
  static int speed_val = 0;

  // Left gauge tile gauges and speedometer
  if (leftGaugeTile) {
    for (int i = 0; i < 3; ++i) {
      Gauge *g = leftGaugeTile->getGauge(i);
      if (!g)
        continue;
      int step = (rand() % 7) - 3; // -3..3
      int val = left_vals[i] + step;
      if (val < 0)
        val = 0;
      if (val > 10)
        val = 10;
      left_vals[i] = val;
      g->setValue(val / 10.0f);
    }

    SevenSegmentDisplay *disp = leftGaugeTile->getDisplay();
    if (disp) {
      int step = (rand() % 7) - 3; // -3..3
      int val = speed_val + step;
      if (val < 0)
        val = 0;
      if (val > 999)
        val = 999;
      speed_val = val;
      disp->setValue(val);
    }
  }

  // Right gauge tile gauges
  if (gaugeTile) {
    for (int i = 0; i < 5; ++i) {
      Gauge *g = gaugeTile->getGauge(i);
      if (!g)
        continue;
      int step = (rand() % 7) - 3; // -3..3
      int val = right_vals[i] + step;
      if (val < 0)
        val = 0;
      if (val > 10)
        val = 10;
      right_vals[i] = val;
      g->setValue(val / 10.0f);
    }
  }
}

