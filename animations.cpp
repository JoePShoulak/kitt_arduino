#include "animations.h"

#include "gauge_tile.h"
#include "gauge.h"
#include "seven_segment.h"
#include "voice_tile.h"
#include <GigaAudio.h>
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

void voice_anim_cb(lv_timer_t *t) {
  static float level = 0.f;
  static float target = 0.f;
  static int hold = 0;
  static bool was_playing = false;
  GigaAudio *audio =
      t ? static_cast<GigaAudio *>(lv_timer_get_user_data(t)) : nullptr;
  bool playing = audio && audio->isPlaying();

  if (!playing) {
    if (was_playing && voiceTile) {
      if (voiceTile->getIndicator(0))
        voiceTile->getIndicator(0)->toggle(false);
      if (voiceTile->getVisualiser())
        voiceTile->getVisualiser()->startFade();
    }
    was_playing = false;
    target = 0.f;
    level = 0.f;
    return;
  }

  if (!was_playing && voiceTile && voiceTile->getIndicator(0))
    voiceTile->getIndicator(0)->toggle(true);
  was_playing = true;

  if (--hold <= 0) {
    if (target > 0.05f) {
      target = 0.f;                   // short pause between words
      hold = 2 + rand() % 3;          // 100-200 ms
    } else {
      target = 0.3f + (rand() % 70) / 100.f; // new burst 0.3-1.0
      hold = 2 + rand() % 5;         // 100-300 ms
    }
  }

  level += (target - level) * 0.25f; // smooth towards target

  if (voiceTile && voiceTile->getVisualiser())
    voiceTile->getVisualiser()->setLevel(level);
}
