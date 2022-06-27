#include <cmath>
#include <fstream>
#include <iostream>
#include "sine.h"

using std::cout;
using std::endl;

const double AMPLITUDE = 0.5;

Sine::Sine(Settings &s)
: Instrument(s)
{
    cout << "Sine initialized" << endl;
}

void Sine::setFrequency(double freq)
{
    auto sampleRate = static_cast<double>(settings().sampleRate());
    m_phaseStep = static_cast<double>(m_samples) * freq / sampleRate;
    generateTable();
}

// Use linear interpolation to get wavetable sample
double Sine::getSample()
{
    auto y = 0.8 * getSampleForCursor(m_cursor);
    incrementPhase();
    return y;
}

void Sine::generateTable()
{
    if (!m_phaseStep) {
        cout << "Error: not initialized" << endl;
        return;
    }

    auto samples = settings().sampleCount();
    for (int i = 0; i < m_samples; ++i) {
        double a = std::sin(2 * M_PI * i / m_samples);
        m_table.push_back(a);
    }
    m_table.push_back(0);
}

void Sine::incrementPhase()
{
    if ((m_cursor += m_phaseStep) > static_cast<double>(m_samples)) {
        m_cursor -= m_samples;
    }
}

// Linear interpolation
double Sine::getSampleForCursor(double cursor)
{
    int x0 = (int)cursor;
    int x1 = x0 + 1;
    double m = cursor - x0;
    double y0 = m_table.at(x0);
    double y1 = m_table.at(x1);
    return y0 + m * (y1 - y0);
}
