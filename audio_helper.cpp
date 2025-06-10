#include "audio_helper.h"

#include <Arduino.h>
#include <GigaAudio.h>

static GigaAudio audio("USB DISK");
static const char *audio_files[] = {"intro.wav", "explode.wav", "shoe.wav", "joseph.wav"};
static const int audio_file_count =
    sizeof(audio_files) / sizeof(audio_files[0]);
static int current_audio_index = 0;

static bool load_current_audio() {
  int attempts = 0;
  while (attempts < audio_file_count) {
    if (audio.load(const_cast<char *>(audio_files[current_audio_index]))) {
      return true;
    }

    if (audio.hasError()) {
      Serial.println(audio.errorMessage());
    } else {
      Serial.print("Cannot load WAV file ");
      Serial.println(audio_files[current_audio_index]);
    }

    // Move to the next track and try again
    current_audio_index = (current_audio_index + 1) % audio_file_count;
    attempts++;
  }
  return false;
}

void audio_setup() {
  current_audio_index = 0;
  if (load_current_audio()) {
    audio.play();
  }
}

void audio_loop() {
  if (audio.isFinished()) {
    current_audio_index = (current_audio_index + 1) % audio_file_count;
    if (load_current_audio()) {
      audio.play();
      Serial.println("Restarting . . .");
    }
  }
}
