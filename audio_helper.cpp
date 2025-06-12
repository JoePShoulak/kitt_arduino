#include "audio_helper.h"

#include <Arduino.h>
#include <GigaAudio.h>

static GigaAudio audio("USB DISK");
void audio_play(const char *file) {
  if (!file)
    return;
  if (!audio.load(const_cast<char *>(file))) {
    if (audio.hasError()) {
      Serial.println(audio.errorMessage());
    } else {
      Serial.print("Cannot load WAV file ");
      Serial.println(file);
    }
    return;
  }
  audio.play();
}
