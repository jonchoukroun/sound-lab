#include <cmath>
#include <fstream>
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

    dft();
    toPolar();

    std::ofstream f;
    f.open("sine.csv");
    f << "Time Domain,,,Frequency Domain\nN,Amplitude,,Freq,M,theta\n";
    for (auto i = 0; i < m_samples; ++i) {
        auto freq = i * m_XN;
        f << i << "," << m_table[i];
        if (i < m_XN) {
            f << ",,";
            f << freq << "," << m_XM[i] << "," << m_XTheta[i] << "\n";
        } else {
            f << "\n";
        }
    }

    f.close();
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

void Sine::dft()
{
    m_XR.fill(0);
    m_XI.fill(0);

    auto N = m_table.size();
    for (auto k = 0; k < m_XN; ++k) {
        for (decltype(N) i = 0; i < N; ++i) {
            m_XR[k] = m_XR[k] + m_table[i] * cos(M_PI * 2 * k * i / N);
            m_XI[k] = m_XI[k] - m_table[i] * sin(M_PI * 2 * k * i / N);
        }
    }
}

void Sine::toPolar()
{
    m_XM.fill(0);
    m_XTheta.fill(0);
    for (auto i = 0; i < m_XN; ++i) {
        m_XM[i] = sqrt(pow(m_XR[i], 2) + pow(m_XI[i], 2));
        m_XTheta[i] = atan(m_XI[i] / m_XR[i]);
    }
}
