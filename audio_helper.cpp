#include "audio_helper.h"
#include "config.h"
#include "voice_tile.h"

#include <Arduino.h>
#include <GigaAudio.h>

GigaAudio audio("USB DISK");
static bool reported = false;

bool load_audio(const char *file)
{
  if (!audio.load(const_cast<char *>(file)))
    return false;

  reported = false;
  return true;
}

void audio_play(const char *file)
{
  if (audio.isPlaying())
    audio.stop();

  if (load_audio(file))
  {
    audio.play();
    voiceTile->getIndicator(0)->toggle(true);
  }
}

void audio_loop()
{
  if (!reported && audio.isFinished())
    reported = true;
}

void audio_stop()
{
  audio.stop();

  reported = false;

  voiceTile->getIndicator(0)->toggle(false);
  voiceTile->getVisualiser()->setLevel(0.f);
}
