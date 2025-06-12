#include "audio_helper.h"

#include <Arduino.h>
#include <GigaAudio.h>

static GigaAudio audio("USB DISK");
static bool audio_loaded = false;
static bool reported = false;
static bool load_audio(const char *file) {
  if (!audio.load(const_cast<char *>(file))) {
    if (audio.hasError()) {
      Serial.println(audio.errorMessage());
    } else {
      Serial.print("Cannot load WAV file ");
      Serial.println(file);
    }
    return false;
  }
  audio_loaded = true;
  reported = false;
  return true;
}

void audio_play(const char *file) {
  if (!file)
    return;
  if (load_audio(file)) {
    audio.play();
  }
}

void audio_loop() {
  if (!audio_loaded)
    return;
  if (!reported && audio.isFinished()) {
    reported = true;
    Serial.println("Audio finished.");
  }
}
