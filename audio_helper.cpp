#include "audio_helper.h"
#include "config.h"
#include "voice_tile.h"

#include <Arduino.h>
#include <GigaAudio.h>

static GigaAudio *audio = nullptr;
static bool audio_loaded = false;
static bool reported = false;

void audio_init(GigaAudio &instance) {
  audio = &instance;
}
static bool load_audio(const char *file) {
  if (!audio || !audio->load(const_cast<char *>(file))) {
    if (audio && audio->hasError()) {
      Serial.println(audio->errorMessage());
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

  if (!audio)
    return;

  if (audio->isPlaying()) {
    audio->stop();
  }

  if (load_audio(file)) {
    audio->play();
    if (voiceTile && voiceTile->getIndicator(0))
      voiceTile->getIndicator(0)->toggle(true);
  }
}

void audio_loop() {
  if (!audio_loaded) {
    return;
  }

  if (audio && !reported && audio->isFinished()) {
    reported = true;
    Serial.println("Audio finished.");
  }
}

bool audio_is_playing() { return audio && audio->isPlaying(); }

void audio_stop() {
  if (!audio || !audio_loaded)
    return;
  if (audio->isPlaying())
    audio->stop();
  audio_loaded = false;
  reported = false;
  if (voiceTile) {
    if (voiceTile->getIndicator(0))
      voiceTile->getIndicator(0)->toggle(false);
    if (voiceTile->getVisualiser())
      voiceTile->getVisualiser()->setLevel(0.f);
  }
}
