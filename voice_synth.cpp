#include "voice_synth.h"

#include "config.h"
#include "voice_tile.h"
#include "audio_helper.h"
#include <stdlib.h>

void voice_anim_cb(lv_timer_t *t) {
  static float level = 0.f;
  static float target = 0.f;
  static int hold = 0;
  (void)t;

  if (!audio_is_playing()) {
    target = 0.f;
    level = 0.f;
    if (voiceTile && voiceTile->getVisualiser())
      voiceTile->getVisualiser()->setLevel(0.f);
    return;
  }

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
