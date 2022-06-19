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
    cout << "Noise initialized" << endl;
}

double Noise::getSample()
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

void Noise::toggleFilter()
{
    m_filter = !m_filter;
}
