#pragma once

#include <array>
#include <cmath>
#include "settings.h"

class WavetableOsc {
public:
    WavetableOsc(Settings &);
    ~WavetableOsc() = default;

    int sampleCount() const;

    // Uses linear interpolation to get samples at any point in the table
    float getAmp(float);

private:
    static constexpr int m_samples = 128;
    std::array<float, m_samples> m_table {0};

    Settings &m_settings;

    void generateTable();
};
