#include "audio_helper.h"
#include "config.h"
#include <voice_tile.h>

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
  if (!file) {
    return;
  }

  if (audio.isPlaying()) {
    audio.stop();
  }

  if (load_audio(file)) {
    audio.play();
    if (voiceTile && voiceTile->getIndicator(0))
      voiceTile->getIndicator(0)->toggle(true);
  }
}

void audio_loop() {
  if (!audio_loaded) {
    return;
  }

  if (!reported && audio.isFinished()) {
    reported = true;
    Serial.println("Audio finished.");
  }
}

bool audio_is_playing() { return audio.isPlaying(); }

void audio_stop() {
  if (!audio_loaded)
    return;
  if (audio.isPlaying())
    audio.stop();
  audio_loaded = false;
  reported = false;
  if (voiceTile) {
    if (voiceTile->getIndicator(0))
      voiceTile->getIndicator(0)->toggle(false);
    if (voiceTile->getVisualiser())
      voiceTile->getVisualiser()->setLevel(0.f);
  }
}
