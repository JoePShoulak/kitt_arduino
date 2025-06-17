#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

#include <GigaAudio.h>

extern GigaAudio audio;

void audio_play(const char *file);
void audio_loop();
void audio_stop();
bool load_audio(const char *file);

#endif
