#include "audio_helper.h"

#include <Arduino.h>
#include <GigaAudio.h>

static GigaAudio audio("USB DISK");

void audio_setup() {}

void audio_play_file(const char *filename) {
  if (!audio.load(const_cast<char *>(filename))) {
    if (audio.hasError()) {
      Serial.println(audio.errorMessage());
    } else {
      Serial.print("Cannot load WAV file ");
      Serial.println(filename);
    }
    return;
  }
  audio.play();
}

void audio_stop() { audio.stop(); }

void audio_loop() {
  // Poll library so buffered playback can continue
  if (audio.isFinished()) {
    audio.stop();
  }
}
