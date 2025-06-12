#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

// Load the intro audio file and play it once
void audio_setup();
// Maintains playback state; does not restart the audio track automatically
void audio_loop();

#endif
