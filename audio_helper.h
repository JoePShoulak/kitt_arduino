#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

// Play the specified WAV file once
void audio_play(const char *file);
// Maintains playback state if audio_setup() or audio_play() was called
// Does not restart the audio track automatically
void audio_loop();
// Returns true if audio is currently playing
bool audio_is_playing();
// Stop playback immediately
void audio_stop();

#endif
