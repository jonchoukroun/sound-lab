#ifndef SINE_H
#define SINE_H

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

    bool m_filter = false;
    double a, b = 0.5;
    double last = 0.0;

    void generateTable();
    void incrementPhase();

    double getSampleForCursor(double);
};

#endif
