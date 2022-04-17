#include <cmath>
#include <iostream>
#include "instrument.h"

using std::cout;
using std::endl;

void Instrument::initialize(double F, int N)
{
    m_duration = m_attack + m_decay;

    m_sampleRate = F;
    m_samples = N - 1;
    cout << "Instrument initialized" << endl;
    cout << "F = " << m_sampleRate << " samples per second" << endl;
    cout << "N = " << m_samples << " samples" << endl;
}

void Instrument::setFrequency(double freq)
{
    m_phaseStep = (double)m_samples * freq / m_sampleRate;
    cout << "Frequency set" << endl;
    cout << "f = " << freq << " Hz" << endl;
    cout << "p = " << m_phaseStep << " samples" << endl;

    generateTable();
}

void Instrument::trigger()
{
    m_cursor = 0.0;
    m_elapsed = 0.0;
    m_isPlaying = true;
}

// Use linear interpolation to get wavetable sample
double Instrument::getSample()
{
    int i0 = (int)m_cursor;
    int i1 = i0 + 1;
    double m = m_cursor - i0;
    double s0 = m_table.at(i0);
    double s1 = m_table.at(i1);
    double a = s0 + m * (s1 - s0);

    return getAmplitude() * a;
}

void Instrument::update(double time)
{
    incrementPhase();
    if ((m_elapsed += time) > m_duration) {
        m_isPlaying = false;
    }
}

bool Instrument::isPlaying()
{
    return m_isPlaying;
}

void Instrument::generateTable()
{
    if (!m_phaseStep) {
        cout << "Error: not initialized" << endl;
        return;
    }

    for (int i = 0; i < m_samples; ++i) {
        double a = std::sin(2 * M_PI * i / m_samples);
        m_table.push_back(a);
        m_cursor += m_phaseStep;
    }
    m_table.push_back(0);
}

void Instrument::incrementPhase()
{
    if ((m_cursor += m_phaseStep) > (double)m_samples) {
        m_cursor -= m_samples;
    }
}

double Instrument::getAmplitude()
{
    if (m_elapsed > m_duration) {
        cout << "Error: sample length exceeded" << endl;
        return 0.0;
    } else if (m_elapsed <= m_attack) {
        return 1.0 / m_attack * m_elapsed;
    } else {
        return -1.0 / m_decay * (m_elapsed - m_attack) + 1;
    }
}
