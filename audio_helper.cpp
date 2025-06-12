#include "audio_helper.h"

#include <Arduino.h>
#include <GigaAudio.h>

static GigaAudio audio("USB DISK");
void audio_play(const char *file) {
  if (!file) {
    Serial.println("audio_play called with null file");
    return;
  }

  Serial.print("Attempting to play: ");
  Serial.println(file);

  if (!audio.load(const_cast<char *>(file))) {
    if (audio.hasError()) {
      Serial.println(audio.errorMessage());
    } else {
      Serial.print("Cannot load WAV file ");
      Serial.println(file);
    }
    return;
  }

  Serial.print("Loaded ");
  Serial.print(file);
  Serial.println(" successfully, starting playback");

  audio.play();
}
