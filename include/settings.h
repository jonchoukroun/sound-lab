#pragma once

class Settings {
public:
    Settings() = default;
    ~Settings() = default;

    struct SettingsParameters {
        int sampleRate;
        int sampleCount;
        int bitDepth;
        int channelCount;

        int screenWidth;
        int screenHeight;
    };

    int sampleRate() const;
    void sampleRate(int);

    int sampleCount() const;
    void sampleCount(int);

    int bitDepth() const;
    void bitDepth(int);

    int channelCount() const;
    void channelCount(int);

    int screenWidth() const;
    void screenWidth(int);

    int screenHeight() const;
    void screenHeight(int);

private:
    int m_sampleRate = 44100;
    int m_sampleCount = 1024;
    int m_bitDepth = 16;
    int m_channelCount = 1;

    int m_screenWidth = 640;
    int m_screenHeight = 480;
};
