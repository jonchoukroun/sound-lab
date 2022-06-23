#include <cmath>
#include <fstream>
#include <iostream>
#include "noise.h"

using std::cout;
using std::endl;

const double AMPLITUDE = 0.8;

Noise::Noise()
: m_distribution(0.0, 1.0)
, m_playing(false)
{
    // generateTable();

    // m_signal.resize(m_samples);
    // for (auto i = 0; i < m_samples; ++i) {
    //     m_signal.at(i) = m_table.at(i);
    // }

    DFT::DFTParams p {
        .filename = "noise.csv",
        .samplesCount = m_samples
    };
    m_DFT.setup(p);

    cout << "Noise initialized" << endl;
}

void Noise::trigger()
{
    if (m_playing) {
        m_playing = false;
        m_DFT.run();
    } else {
        m_playing = true;
    }
}

double Noise::generateSample()
{
    double s = m_distribution(m_generator) * 0.25 - 0.125;
    m_DFT.storeSignal(s);
    return s;
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
