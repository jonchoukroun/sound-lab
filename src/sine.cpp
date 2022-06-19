#include <cmath>
#include <iostream>
#include "sine.h"

using std::cout;
using std::endl;

const double AMPLITUDE = 0.5;

Sine::Sine(Settings &s)
: m_sampleRate(s.sampleRate)
, m_samples(s.sampleSize - 1)
, m_cursorF(0.0)
, m_cursorH1(0.0)
, m_cursorH2(0.0)
{
    cout << "Sine initialized" << endl;
}

void Sine::setFrequency(double freq)
{
    m_phaseStepF = (double)m_samples * freq / m_sampleRate;
    m_phaseStepH1 = (double)m_samples * (freq * 2.0) / m_sampleRate;
    m_phaseStepH2 = (double)m_samples * (freq * 4.0) / m_sampleRate;
    generateTable();
}

// Use linear interpolation to get wavetable sample
double Sine::getSample()
{
    auto f = 0.8 * getSampleForCursor(m_cursorF);
    auto h1 = 0.6 * getSampleForCursor(m_cursorH1);
    auto h2 = 0.4 * getSampleForCursor(m_cursorH2);
    incrementPhase();
    double y = (f + h1 + h2);
    double sum = a * last + b * y;
    last = y;
    return m_filter ? sum : y;
}

void Sine::toggleFilter()
{
    m_filter = !m_filter;
}

void Sine::generateTable()
{
    if (!m_phaseStepF || !m_phaseStepH1 || !m_phaseStepH2) {
        cout << "Error: not initialized" << endl;
        return;
    }

    for (int i = 0; i < m_samples; ++i) {
        double a = std::sin(2 * M_PI * i / m_samples);
        m_table.push_back(a);
    }
    m_table.push_back(0);
}

void Sine::incrementPhase()
{
    if ((m_cursorF += m_phaseStepF) > (double)m_samples) {
        m_cursorF -= m_samples;
    }
    if ((m_cursorH1 += m_phaseStepH1) > (double)m_samples) {
        m_cursorH1 -= m_samples;
    }
    if ((m_cursorH2 += m_phaseStepH2) > (double)m_samples) {
        m_cursorH2 -= m_samples;
    }
}

double Sine::getSampleForCursor(double cursor)
{
    int x0 = (int)cursor;
    int x1 = x0 + 1;
    double m = cursor - x0;
    double y0 = m_table.at(x0);
    double y1 = m_table.at(x1);
    return y0 + m * (y1 - y0);
}
