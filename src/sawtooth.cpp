#include "sawtooth.h"

using std::cout;
using std::endl;

Sawtooth::Sawtooth(Settings &s)
: Instrument(s)
, m_wavetable(s, WavetableOsc::Sawtooth)
{
    cout << "Sawtooth initialized" << endl;
}

void Sawtooth::setFrequency(int f)
{
    auto sampleRate = static_cast<double>(settings().sampleRate());
    m_phaseStep = static_cast<double>(m_wavetable.sampleCount()) * f / sampleRate;
}

double Sawtooth::processAudio()
{
    auto y = 0.8 * static_cast<double>(m_wavetable.getAmp(m_cursor));
    incrementPhase();
    return y;
}

void Sawtooth::incrementPhase()
{
    auto samples = m_wavetable.sampleCount();
    if ((m_cursor += m_phaseStep) > static_cast<double>(samples)) {
        m_cursor -= samples;
    }
}
