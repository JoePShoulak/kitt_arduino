#include "audio_helper.h"
#include <Arduino.h>

static GigaAudio *audio = nullptr;

static const char *audio_files[] = {"intro.wav", "explode.wav", "shoe.wav"};
static const int audio_file_count = sizeof(audio_files) / sizeof(audio_files[0]);
static int current_audio_index = 0;

void audio_setup() {
    if (!audio)
        audio = new GigaAudio("USB DISK");
    current_audio_index = 0;
    play_current_audio();
}

bool load_current_audio() {
    if (!audio || !audio->load(const_cast<char *>(audio_files[current_audio_index]))) {
        if (audio && audio->hasError()) {
            Serial.println(audio->errorMessage());
        } else {
            Serial.print("Cannot load WAV file ");
            Serial.println(audio_files[current_audio_index]);
        }
        return false;
    }
    return true;
}

bool play_audio_file(const char *filename) {
    if (!audio || !audio->load(const_cast<char *>(filename))) {
        if (audio && audio->hasError())
            Serial.println(audio->errorMessage());
        else {
            Serial.print("Cannot load WAV file ");
            Serial.println(filename);
        }
        return false;
    }
    audio->play();
    return true;
}

bool play_current_audio() {
    if (!load_current_audio())
        return false;
    audio->play();
    return true;
}

void audio_loop() {
    if (audio && audio->isFinished()) {
        current_audio_index = (current_audio_index + 1) % audio_file_count;
        if (play_current_audio()) {
            Serial.println("Restarting . . .");
        }
    }
}
