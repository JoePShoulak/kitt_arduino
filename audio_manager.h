#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <Arduino.h>

// initialize USB audio playback
void audioSetup();

// play an audio file from the mounted USB drive
bool audioPlay(const char *filename);

// process audio playback tasks (call regularly in loop)
void audioUpdate();

// get current audio level 0.0-1.0 for visualizer
float audioLevel();

#endif // AUDIO_MANAGER_H
