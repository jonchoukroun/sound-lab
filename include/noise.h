#ifndef NOISE_H
#define NOISE_H

#include <array>
#include <random>

const int SAMPLES = 256;
const int SAMPLING_RATE = 44100;

class Noise
{
public:
    Noise();
    ~Noise() = default;

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
    double clampRndSample();

    // DFT analysis
    static const int m_XN = (m_samples / 2) + 1; // 129
    // Rectangular form
    std::array<double, m_XN> m_XR;
    std::array<double, m_XN> m_XI;
    // Polar form
    std::array<double, m_XN> m_XM;
    std::array<double, m_XN> m_XTheta;

    void dft();
    void toPolar();

    // LP Filter
    bool m_filter;
    double a, b = 0.5;
    double last = 0.0;
};

#endif
