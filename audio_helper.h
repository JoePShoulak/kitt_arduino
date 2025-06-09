#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

#include <GigaAudio.h>

// Initialize audio playback. Call once from setup
void audio_setup();

bool load_current_audio();
bool play_audio_file(const char *filename);
bool play_current_audio();
void audio_loop();

#endif
