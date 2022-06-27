#ifndef SINE_H
#define SINE_H

#include <array>
#include <vector>
#include "instrument.h"
#include "settings.h"

class Sine : public Instrument
{
public:
    Sine(Settings &);
    ~Sine() = default;

    void setFrequency(double f);

    double getSample();

private:
    std::vector<double> m_table;
    static constexpr int m_samples = 128;
    double m_phaseStep = 0.0;
    double m_cursor = 0.0;

    bool m_playing = false;

    void generateTable();
    void incrementPhase();
    double getSampleForCursor(double);
};

#endif
