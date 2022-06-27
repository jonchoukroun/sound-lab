#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include "sine.h"

using std::cout;
using std::endl;

const double AMPLITUDE = 0.5;

Sine::Sine(Settings &s)
: Instrument(s)
, m_wavetable(s)
{
    cout << "Sine initialized" << endl;
}

void Sine::setFrequency(double freq)
{
    auto sampleRate = static_cast<double>(settings().sampleRate());
    m_phaseStep = static_cast<double>(m_wavetable.sampleCount()) * freq / sampleRate;
}

double Sine::processAudio()
{
    auto y = 0.8 * static_cast<double>(m_wavetable.getAmp(m_cursor));
    incrementPhase();
    return y;
}

void Sine::incrementPhase()
{
    auto samples = m_wavetable.sampleCount();
    if ((m_cursor += m_phaseStep) > static_cast<double>(samples)) {
        m_cursor -= samples;
    }
}
