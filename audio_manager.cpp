#include "audio_manager.h"

#include <Arduino.h>
#include <FS.h>

AudioManager& AudioManager::instance() {
    static AudioManager instance;
    return instance;
}

bool AudioManager::begin(const char* folder) {
    if (!m_msc.begin()) {
        Serial.println("AudioManager: USB drive not detected");
        return false;
    }

    // wait until the drive is ready
    while (!m_msc.ready()) {
        m_usb.Task();
    }

    m_fs = &m_msc;
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
    if (!m_fs) {
        Serial.println("AudioManager: filesystem not ready");
        return;
    }

    File dir = m_fs->open(folder);
    if (!dir) {
        Serial.println("AudioManager: failed to open directory");
        return;
    }

    File entry;
    while ((entry = dir.openNextFile())) {
        if (!entry.isDirectory()) {
            String name = entry.name();
            name.toLowerCase();
            if (name.endsWith(".mp3") || name.endsWith(".wav")) {
                m_files.push_back(String(entry.name()));
            }
        }
        entry.close();
    }
    dir.close();
}

void AudioManager::update() {
    if (!m_playing)
        return;

    if (!m_file || !m_file.available()) {
        stop();
        return;
    }

    while (m_file.available() && I2S.availableForWrite() >= (int)sizeof(m_buffer)) {
        size_t bytesRead = m_file.read((uint8_t*)m_buffer, sizeof(m_buffer));
        if (!bytesRead) {
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
    if (!filename || !*filename || !m_fs)
        return false;

    stop();

    String path = String(m_folder) + "/" + filename;
    m_file = m_fs->open(path.c_str());
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
        I2S.end();
        if (m_file)
            m_file.close();
        m_playing = false;
        m_loudness = 0.0f;
    }
}
