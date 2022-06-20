#ifndef SINE_H
#define SINE_H

#include <array>
#include <vector>

class Sine
{
public:
    struct Settings {
        double sampleRate;
        int sampleSize;
    };

    Sine(Settings &);
    ~Sine() = default;

    void setFrequency(double f);

    double getSample();

    void toggleFilter();

private:
    double m_sampleRate;
    // Wavetable size
    int m_samples;
    // Frequence-based wavetable index increment
    double m_phaseStepF;
    double m_phaseStepH1;
    double m_phaseStepH2;
    // Current position in wavetable
    double m_cursorF;
    double m_cursorH1;
    double m_cursorH2;

    std::vector<double> m_table;

    void generateTable();
    void incrementPhase();

    // DFT analysis
    static const int m_XN = 128;
    // Rectangular form
    std::array<double, m_XN> m_XR;
    std::array<double, m_XN> m_XI;
    // Polar form
    std::array<double, m_XN> m_XM;
    std::array<double, m_XN> m_XTheta;

    void dft();
    void toPolar();

    bool m_filter = false;
    double a, b = 0.5;
    double last = 0.0;
    double getSampleForCursor(double);
};

#endif
