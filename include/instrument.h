#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <vector>
#include <cmath>

class Instrument
{
public:
    void initialize(double F, int N);
    void setFrequency(double f);

    void trigger();

    double getSample();
    void update(double time);

    bool isPlaying();

private:
    double m_sampleRate;
    // Wavetable size
    int m_samples;

    // Frequence-based wavetable index increment
    double m_phaseStep;
    // Current position in wavetable
    double m_cursor;

    // Hard coded envelope
    const double m_attack = 0.0;
    const double m_decay= 0.3;
    // Length of sound, in seconds
    double m_duration;
    double m_elapsed;

    bool m_isPlaying;

    std::vector<double> m_table;

    void generateTable();
    void incrementPhase();

    double getAmplitude();
};

#endif
