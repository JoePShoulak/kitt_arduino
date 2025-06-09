#include "audio_manager.h"

#include <Arduino.h>
#include <mbed.h>
#include <dirent.h>
#include <cstdio>

AudioManager& AudioManager::instance() {
    static AudioManager instance;
    return instance;
}

AudioManager::AudioManager() : m_fs("fs") {}

AudioManager::~AudioManager() {
    stop();
    I2S.end();
    m_fs.unmount();
    m_msd.disconnect();
}

bool AudioManager::begin(const char* folder) {
    if (!m_msd.connect()) {
        Serial.println("AudioManager: USB drive not detected");
        return false;
    }

    if (m_fs.mount(&m_msd) != 0) {
        Serial.println("AudioManager: failed to mount filesystem");
        return false;
    }

    m_folder = String(folder);
    scanFolder(folder);

    if (!I2S.begin(I2S_PHILIPS_MODE, 44100, 16)) {
        Serial.println("AudioManager: failed to start I2S");
        return false;
    }

    return true;
}

void AudioManager::scanFolder(const char* folder) {
    m_files.clear();

    char path[256];
    snprintf(path, sizeof(path), "/fs/%s", folder);

    DIR* dir = opendir(path);
    if (!dir) {
        Serial.println("AudioManager: failed to open directory");
        return;
    }

    struct dirent* ent;
    while ((ent = readdir(dir)) != nullptr) {
        if (ent->d_type != DT_DIR) {
            String name = ent->d_name;
            name.toLowerCase();
            if (name.endsWith(".mp3") || name.endsWith(".wav")) {
                m_files.push_back(String(ent->d_name));
            }
        }
    }
    closedir(dir);
}

void AudioManager::update() {
    if (!m_playing)
        return;

    if (!m_file || feof(m_file)) {
        stop();
        return;
    }

    while (!feof(m_file) && I2S.availableForWrite() >= (int)sizeof(m_buffer)) {
        size_t bytesRead = fread(m_buffer, 1, sizeof(m_buffer), m_file);
        if (bytesRead == 0) {
            stop();
            break;
        }

        uint32_t sum = 0;
        size_t samples = bytesRead / 2;
        for (size_t i = 0; i < samples; ++i) {
            int16_t s = m_buffer[i];
            sum += abs(s);
        }
        m_loudness = sum / (float)(samples * 32768.0f);

        I2S.write(m_buffer, bytesRead);
    }
}

bool AudioManager::play(const char* filename) {
    if (!filename || !*filename)
        return false;

    stop();

    char path[256];
    snprintf(path, sizeof(path), "/fs/%s/%s", m_folder.c_str(), filename);
    m_file = fopen(path, "rb");
    if (!m_file) {
        Serial.println("AudioManager: failed to open file");
        return false;
    }

    m_playing = true;
    m_loudness = 0.0f;
    return true;
}

bool AudioManager::isPlaying() const {
    return m_playing;
}

float AudioManager::getLoudness() const {
    return m_loudness;
}

const std::vector<String>& AudioManager::files() const {
    return m_files;
}

void AudioManager::stop() {
    if (m_playing) {
        I2S.flush();
        if (m_file) {
            fclose(m_file);
            m_file = nullptr;
        }
        m_playing = false;
        m_loudness = 0.0f;
    }
}
