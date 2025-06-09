#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <Arduino.h>
#include <mbed.h>
#include <USBHostMSD.h>
#include <FATFileSystem.h>
#include <I2S.h>
#include <vector>

// Simple wrapper for asynchronous audio playback from a USB drive
class AudioManager {
public:
    // Access singleton instance
    static AudioManager& instance();

    // Initialize the manager and scan the given folder for playable files
    bool begin(const char* folder);

    // Update playback state; call regularly in the main loop
    void update();

    // Begin playing the provided file name (must exist in scanned folder)
    bool play(const char* filename);

    // True if a file is currently playing
    bool isPlaying() const;

    // Current loudness of playback as a value in the range [0,1]
    float getLoudness() const;

    // List of discovered audio files
    const std::vector<String>& files() const;

private:
    AudioManager();
    void scanFolder(const char* folder);
    void stop();

    USBHostMSD m_msd{"usb"};
    mbed::FATFileSystem m_fs{"fs"};
    FILE* m_file = nullptr;
    std::vector<String> m_files;
    String m_folder;
    bool m_playing = false;
    float m_loudness = 0.0f;
    static constexpr size_t BUFFER_SIZE = 1024;
    int16_t m_buffer[BUFFER_SIZE / 2];
};

#endif // AUDIO_MANAGER_H
