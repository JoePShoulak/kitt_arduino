#include "audio_manager.h"
#include <USBHost.h>
#include <Audio.h>

// USB host and mass storage objects
static USBHost usb;
static MassStorage ms(usb);
static AudioPlayer player;
static File audioFile;

void audioSetup() {
    usb.begin();
    delay(200);
    ms.begin();
    player.begin();
}

bool audioPlay(const char *filename) {
    if (audioFile) {
        player.stop();
        audioFile.close();
    }
    audioFile = ms.open(filename);
    if (!audioFile) {
        return false;
    }
    player.play(audioFile);
    return true;
}

void audioUpdate() {
    usb.Task();
    player.tick();
}

float audioLevel() {
    return player.getLevel();
}

