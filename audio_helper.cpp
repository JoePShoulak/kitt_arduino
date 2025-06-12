#include "audio_helper.h"

#include <Arduino.h>
#include <GigaAudio.h>

static GigaAudio audio("USB DISK");
static const char *audio_file = "intro.wav"; // single track to play
static bool audio_loaded = false;

static bool load_audio() {
  if (!audio.load(const_cast<char *>(audio_file))) {
    if (audio.hasError()) {
      Serial.println(audio.errorMessage());
    } else {
      Serial.print("Cannot load WAV file ");
      Serial.println(audio_file);
    }
    return false;
  }
  audio_loaded = true;
  return true;
}

void audio_setup() {
  if (load_audio()) {
    audio.play();
  }
}

void audio_loop() {
  if (!audio_loaded)
    return;
  static bool reported = false;
  if (!reported && audio.isFinished()) {
    reported = true;
    Serial.println("Audio finished.");
  }
}
