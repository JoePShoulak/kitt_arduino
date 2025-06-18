// audio_helper.cpp

#include "audio_helper.h"

GigaAudio audio("USB DISK");

void audio_play(const char *file)
{
  if (audio.isPlaying())
    audio.stop();

  if (audio.load(const_cast<char *>(file)))
    audio.play();
}
