#ifndef NOISE_H
#define NOISE_H

#include <array>
#include <random>
#include <vector>
#include "dft.h"
#include "instrument.h"
#include "settings.h"

class Noise : public Instrument
{
public:
    Noise(Settings &);
    ~Noise() = default;

    double processAudio();

private:
    std::default_random_engine m_generator;
    std::uniform_real_distribution<double> m_distribution;

    bool m_playing;
};

#endif
