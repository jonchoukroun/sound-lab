#include <iostream>
#include "wavetable_osc.h"

using std::cout;
using std::endl;

WavetableOsc::WavetableOsc(Settings &s)
: m_settings(s)
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
    auto samples = m_table.size();
    for (decltype(samples) i = 0; i < samples; ++i) {
        auto a = static_cast<float>(std::sin(2 * M_PI * i / samples));
        m_table.at(i) = a;
    }
}
