#include <iostream>
#include "wavetable_osc.h"

using std::cout;
using std::endl;

WavetableOsc::WavetableOsc(Settings &s, Waveform w)
: m_settings(s)
, m_waveform(w)
{
    generateTable();
}

int WavetableOsc::sampleCount() const
{
    return m_samples;
}

float WavetableOsc::getAmp(float cursor)
{
    int x0 = static_cast<int>(cursor) % (m_table.size() - 1);
    int x1 = (x0 + 1) % (m_table.size() - 1);
    float mid = cursor - x0;
    float y0 = m_table.at(x0);
    float y1 = m_table.at(x1);
    return y0 + mid * (y1 - y0);
}

void WavetableOsc::generateTable()
{
    cout << "WavetableOsc#generateTable | samples " << m_samples << endl;
    switch (m_waveform) {
        case Sine:
            generateSineTable();
            break;
        case Sawtooth:
            generateSawtoothTable();
            break;
    }
    auto size = m_table.size();
}

void WavetableOsc::generateSineTable()
{
    for (auto i = 0; i < m_samples - 1; ++i) {
        m_table.at(i) = static_cast<float>(std::sin(2 * M_PI * i / (m_samples - 1)));
    }
    m_table.at(m_samples - 1) = 0.0;
}

// TODO: fix and replace with this additive sine approach
void WavetableOsc::generateSawtoothTable()
{
    for (auto i = 0; i < m_samples - 1; ++i) {
        auto y = 0.f;
        for (auto j = 1; j < 257; ++j) {
            y += pow(-1, j) / j * sin(2 * M_PI * j * i / (m_samples - 1));
        }
        m_table.at(i) = (-2 / M_PI) * y;
        cout << i << " " << m_table.at(i) << endl;
    }
}
