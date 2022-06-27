#include <cmath>
#include <fstream>
#include <iostream>
#include "noise.h"

using std::cout;
using std::endl;

Noise::Noise(Settings &)
: m_distribution(0.0, 1.0)
, m_playing(false)
{
    cout << "Noise initialized" << endl;
}

void Noise::trigger()
{
    if (m_playing) {
        m_playing = false;
    } else {
        m_playing = true;
    }
}

double Noise::generateSample()
{
    double s = m_distribution(m_generator) * 0.25 - 0.125;
    return s;
}
