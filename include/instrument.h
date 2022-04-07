#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <vector>
#include <cmath>

class Instrument
{
public:
    void generateTable(double freq);

    float getSample();

    void cursorInc();

private:
    static constexpr double m_period = 2 * M_PI;
    static const int m_tableSize = 64;
    static constexpr float m_sampleSize = 44100.0;

    std::vector<float> m_wavetable;

    float m_cursor;
    float m_step;

    double m_freq;

    float linInterpol();
};

#endif
