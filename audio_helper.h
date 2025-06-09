#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

#include <GigaAudio.h>

extern GigaAudio audio;

bool load_current_audio();
bool play_audio_file(const char *filename);
bool play_current_audio();
void audio_loop();

#endif
