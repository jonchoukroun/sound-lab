#include <cmath>
#include "instrument.h"

void Instrument::generateTable(double freq)
{
    m_freq = freq;
    if (m_freq == 0) return;

    for (size_t i = 0; i != m_tableSize; ++i) {
        // OK to cast, won't lose precision with possible table size
        double v = sin(m_period * static_cast<float>(i) / m_tableSize);
        m_wavetable.push_back(v);
    }

    m_cursor = 0.0;
    m_step = m_freq * static_cast<float>(m_wavetable.size()) / m_sampleSize;
}

float Instrument::getSample()
{
    m_cursor = fmod(m_cursor, static_cast<float>(m_wavetable.size()));
    auto sample = linInterpol();
    m_cursor += m_step;
    return sample;
}

float Instrument::linInterpol()
{
    auto floor = static_cast<typename decltype(m_wavetable)::size_type>(m_cursor);
    auto ceil = static_cast<typename decltype(m_wavetable)::size_type>(std::ceil(m_cursor)) % m_wavetable.size();
    auto ceilWeight = m_cursor - static_cast<float>(floor);
    return m_wavetable.at(m_cursor) * ceilWeight + (1.f - ceilWeight) * m_wavetable.at(floor);
}
