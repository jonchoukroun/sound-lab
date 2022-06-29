#pragma once

#include <array>
#include <cmath>
#include "settings.h"

class WavetableOsc {
public:
    enum Waveform { Sine, Sawtooth };

    WavetableOsc(Settings &, Waveform);
    ~WavetableOsc() = default;

    int sampleCount() const;

    // Uses linear interpolation to get samples at any point in the table
    float getAmp(float);

private:
    static constexpr int m_samples = 129;
    std::array<float, m_samples> m_table {0.f};

    Settings &m_settings;

    Waveform m_waveform;

    void generateTable();
    void generateSineTable();
    void generateSawtoothTable();
};
