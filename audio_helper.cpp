#include "audio_helper.h"

#include <Arduino.h>
#include <GigaAudio.h>
#include <Arduino_USBHostMbed5.h>

static GigaAudio audio("USB DISK");
USBHostMSD msd; // Mass Storage Device driver
static bool usb_available = false;
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

void audio_setup() {
  // attempt to connect once during setup
  if (msd.connect()) {
    Serial.println("USB Disk connected");
    usb_available = true;
  } else {
    Serial.println("USB Disk not found");
    usb_available = false;
    return; // skip audio initialisation when no drive is attached
  }

  current_audio_index = 0;
  if (load_current_audio()) {
    audio.play();
  }
}

void audio_loop() {
  // reconnect if the drive has been inserted after startup
  if (!msd.connected()) {
    if (msd.connect()) {
      Serial.println("USB Disk connected");
      usb_available = true;
      current_audio_index = 0;
      if (load_current_audio()) {
        audio.play();
      }
    } else {
      usb_available = false;
      return; // nothing to do without a drive
    }
  }

  if (!usb_available) {
    return;
  }
  if (audio.isFinished()) {
    current_audio_index = (current_audio_index + 1) % audio_file_count;
    if (load_current_audio()) {
      audio.play();
      Serial.println("Restarting . . .");
    }
  }
}
