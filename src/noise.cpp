#include <cmath>
#include <fstream>
#include <iostream>
#include "noise.h"

using std::cout;
using std::endl;

Noise::Noise(Settings &s)
: Instrument(s)
, m_distribution(0.0, 1.0)
, m_playing(false)
{
    cout << "Noise initialized" << endl;
}

double Noise::processAudio()
{
    return m_distribution(m_generator) * 0.25 - 0.125;
}
