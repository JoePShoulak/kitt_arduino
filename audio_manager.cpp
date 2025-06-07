#include "audio_manager.h"
#include <Arduino_USBHostMbed5.h>
#include <Audio.h>
#include <FATFileSystem.h>

// USB host and mass storage objects
static USBHostMSD msd;
static mbed::FATFileSystem usbfs("usb");
static AudioPlayer player;
static FILE *audioFile = nullptr;

void audioSetup() {
    while (!msd.connect()) {
        delay(100);
    }
    usbfs.mount(&msd);
    player.begin();
}

bool audioPlay(const char *filename) {
    if (audioFile) {
        player.stop();
        fclose(audioFile);
    }
    char path[64];
    snprintf(path, sizeof(path), "/usb/%s", filename);
    audioFile = fopen(path, "rb");
    if (!audioFile) {
        return false;
    }
    player.play(audioFile);
    return true;
}

void audioUpdate() {
    if (!msd.connected()) {
        msd.connect();
    }
    player.tick();
}

float audioLevel() {
    return player.getLevel();
}

