#include "voice_synth.h"

#include "config.h"
#include "voice_tile.h"
#include "audio_helper.h"
#include <GigaAudio.h>
#include <stdlib.h>

void voice_anim_cb(lv_timer_t *t) {
  static float level = 0.f;
  static float target = 0.f;
  static int hold = 0;
  static bool was_playing = false;
  GigaAudio *audio =
      t ? static_cast<GigaAudio *>(lv_timer_get_user_data(t)) : nullptr;
  bool playing = audio ? audio->isPlaying() : audio_is_playing();

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
