#pragma once

#include <array>
#include <vector>
#include "instrument.h"
#include "settings.h"
#include "wavetable_osc.h"

class Sine : public Instrument
{
public:
    Sine(Settings &);
    ~Sine() = default;

    void setFrequency(double f);

    double processAudio();

private:
    WavetableOsc m_wavetable;
    double m_phaseStep = 0.0;
    double m_cursor = 0.0;

    bool m_playing = false;

    void incrementPhase();
};
