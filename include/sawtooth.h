#pragma once

#include <iostream>
#include <vector>
#include "instrument.h"
#include "settings.h"
#include "wavetable_osc.h"

class Sawtooth : public Instrument
{
public:
    Sawtooth(Settings &);
    ~Sawtooth() = default;

    void setFrequency(int);

    double processAudio();

private:
    WavetableOsc m_wavetable;
    double m_cursor = 0.0;
    double m_phaseStep = 0.0;

    void incrementPhase();
};
