#include "animations.h"

#include <Arduino.h>
#include <GigaAudio.h>
#include "../tiles/gauge_tile.h"
#include "../tiles/voice_tile.h"
#include "gauge.h"
#include "seven_segment.h"
#include "../UI.h"

int drunken_walk(int val, int max_step, int max_val, int min_val = 0)
{
  int step = (rand() % (2 * max_step + 1) - max_step);
  return constrain(val + step, min_val, max_val);
}

void gauge_anim_cb(lv_timer_t *t)
{
  static int speed_val = 0;

  for (int i = 0; i < 3; ++i)
    ui.leftGaugeTile->getGauge(i)->drunken_walk();

  for (int i = 0; i < 5; ++i)
    ui.rightGaugeTile->getGauge(i)->drunken_walk();

  SevenSegmentDisplay *disp = ui.leftGaugeTile->getSevenSegmentDisplay();
  speed_val = drunken_walk(speed_val, 3, 999);
  disp->setValue(speed_val);
}

void voice_anim_cb(lv_timer_t *t)
{
  static float level = 0.f;
  static float target = 0.f;
  static int hold = 0;
  static bool was_playing = false;
  GigaAudio *audio = static_cast<GigaAudio *>(lv_timer_get_user_data(t));

  if (!audio->isPlaying())
  {
    if (was_playing)
    {
      ui.voiceTile->indicators[0]->toggle(false);
      ui.voiceTile->visualiser->startFade();
    }

    was_playing = false;
    target = 0.f;
    level = 0.f;

    return;
  }

  if (!was_playing)
  {
    ui.voiceTile->indicators[0]->toggle(true);
    was_playing = true;
  }

  if (--hold <= 0)
  {
    if (target > 0.05f)
    {
      target = 0.f;          // short pause between words
      hold = 2 + rand() % 3; // 100-200 ms
    }
    else
    {
      target = 0.3f + (rand() % 70) / 100.f; // new burst 0.3-1.0
      hold = 2 + rand() % 5;                 // 100-300 ms
    }
  }

  level += (target - level) * 0.25f; // smooth towards target

  ui.voiceTile->visualiser->setLevel(level);
}
