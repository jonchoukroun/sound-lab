#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <vector>
#include <cmath>
#include "envelope.h"

class Instrument
{
public:
    struct Settings {
        double sampleRate;
        int sampleSize;
        double frequency;
        Envelope &ampEnv;
    };

    Instrument(Settings &);
    ~Instrument() = default;

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

    double m_elapsed;

    bool m_isPlaying;

    std::vector<double> m_table;

    void generateTable();
    void incrementPhase();

    Envelope &m_ampEnv;
};

#endif
