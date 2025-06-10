#include "audio_helper.h"

#include <Arduino.h>
#include <GigaAudio.h>

static GigaAudio audio("USB DISK");
static bool audio_enabled = false;
static const char *audio_files[] = {"intro.wav", "explode.wav", "shoe.wav", "joseph.wav"};
static const int audio_file_count =
    sizeof(audio_files) / sizeof(audio_files[0]);
static int current_audio_index = 0;

static bool load_current_audio() {
  if (!audio.load(const_cast<char *>(audio_files[current_audio_index]))) {
    if (audio.hasError()) {
      Serial.println(audio.errorMessage());
    } else {
      Serial.print("Cannot load WAV file ");
      Serial.println(audio_files[current_audio_index]);
    }
    return false;
  }
  return true;
}

bool audio_setup(unsigned long timeout_ms) {
  Serial.println("Initializing audio . . .");
  if (audio.hasError()) {
    Serial.println(audio.errorMessage());
    return false;
  }
  current_audio_index = 0;
  unsigned long start = millis();

  Serial.println("Made it here");
  return true; 
}

void audio_loop() {
  if (!audio_enabled)
    return;
  if (audio.isFinished()) {
    current_audio_index = (current_audio_index + 1) % audio_file_count;
    if (load_current_audio()) {
      audio.play();
      Serial.println("Restarting . . .");
    }
  }
}
