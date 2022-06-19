#ifndef NOISE_H
#define NOISE_H

#include <random>

const int SAMPLES = 512;

class Noise
{
public:
    Noise();
    ~Noise() = default;

    double getSample();
    void toggleFilter();

private:
    std::default_random_engine m_generator;
    std::uniform_real_distribution<double> m_distribution;

    // LP Filter
    bool m_filter;
    double a, b = 0.5;
    double last = 0.0;
};

#endif
