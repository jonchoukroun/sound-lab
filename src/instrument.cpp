#include <cmath>
#include <iostream>
#include "instrument.h"

using std::cout;
using std::endl;

void Instrument::initialize(double F, int N)
{
    m_sampleRate = F;
    m_samples = N - 1;
    m_step = 2 * M_PI / m_samples;
    cout << "Instrument initialized" << endl;
    cout << "F = " << m_sampleRate << " samples per second" << endl;
    cout << "N = " << m_samples << " samples" << endl;
    cout << "s = " << m_step << endl;

    generateTable();
}


void Instrument::setFrequency(double freq)
{
    m_step = (double)m_samples * freq / m_sampleRate;
    cout << "Frequency set" << endl;
    cout << "f = " << freq << " Hz" << endl;
    cout << "p = " << m_step << " samples" << endl;
}

void Instrument::generateTable()
{
    if (!m_step) {
        cout << "Error: not initialized" << endl;
        return;
    }

    for (int i = 0; i < m_samples; ++i) {
        double a = std::sin(m_cur);
        m_table.push_back(a);
        m_cur += m_step;
    }
    m_table.push_back(0);
}

void Instrument::start()
{
    m_cur = 0.0;
    m_isPlaying = true;
}

void Instrument::stop()
{
    m_isPlaying = false;
}

double Instrument::getAmplitude()
{
    int i0 = (int)m_cur;
    int i1 = i0 + 1;
    double m = m_cur - i0;
    double s0 = m_table.at(i0);
    double s1 = m_table.at(i1);
    double a = s0 + m * (s1 - s0);

    if ((m_cur += m_step) > (double)m_samples) {
        m_cur -= m_samples;
    }

    return a;
}

bool Instrument::isPlaying()
{
    return m_isPlaying;
}
