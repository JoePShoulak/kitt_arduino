// audio_helper.h

#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

#include <GigaAudio.h>

extern GigaAudio audio;

void audio_init();

void audio_play(const char *file);

#endif
