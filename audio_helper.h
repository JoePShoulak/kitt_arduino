#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

// Load the intro audio file and play it once
void audio_setup();
// Play the specified WAV file once
void audio_play(const char *file);
// Maintains playback state if audio_setup() or audio_play() was called
// Does not restart the audio track automatically
void audio_loop();

#endif
