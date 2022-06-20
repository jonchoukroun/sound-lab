#include <cmath>
#include <fstream>
#include <iostream>
#include "noise.h"

using std::cout;
using std::endl;

const double AMPLITUDE = 0.8;

Noise::Noise()
: m_distribution(0.0, 1.0)
{
    generateTable();
    dft();
    toPolar();

    std::ofstream f;
    f.open("noise.csv");
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

    cout << "Noise initialized" << endl;
}

double Noise::generateSample()
{
    while (true) {
        double r = m_distribution(m_generator);
        if (r > -1.0 && r < 1.0) {
            double sum = last * a + r * b;
            last = r;
            return m_filter ? sum : r;
        }
    }
}

double Noise::getSample()
{
    double s = m_table.at(m_cursor);
    if (++m_cursor >= SAMPLES) m_cursor = 0;
    return s;
}

void Noise::toggleFilter()
{
    m_filter = !m_filter;
}

void Noise::generateTable()
{
    for (auto &s : m_table) {
        s = m_distribution(m_generator) * 0.25 - 0.125;
    }
}

void Noise::dft()
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

void Noise::toPolar()
{
    m_XM.fill(0);
    m_XTheta.fill(0);
    for (auto i = 0; i < m_XN; ++i) {
        m_XM[i] = sqrt(pow(m_XR[i], 2) + pow(m_XI[i], 2));
        m_XTheta[i] = atan(m_XI[i] / m_XR[i]);
    }
}
