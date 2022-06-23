#ifndef NOISE_H
#define NOISE_H

#include <array>
#include <random>
#include <vector>
#include "dft.h"

const int SAMPLES = 44100;
const int SAMPLING_RATE = 44100;

class Noise
{
public:
    Noise();
    ~Noise() = default;

    void trigger();

    double generateSample();

    double getSample();

    void toggleFilter();

private:
    std::default_random_engine m_generator;
    std::uniform_real_distribution<double> m_distribution;

    static const int m_samples = SAMPLES;
    std::array<double, m_samples> m_table;
    int m_cursor = 0;

    void generateTable();

    bool m_playing;

    // DFT analysis
    DFT m_DFT;

    // LP Filter
    bool m_filter;
    double a, b = 0.5;
    double last = 0.0;
};

#endif
