#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <vector>
#include <cmath>

class Instrument
{
public:
    void initialize(double F, int N);
    void setFrequency(double f);
    void setDuration(double d);

    void trigger();

    double getAmplitude();
    void update(double time);

    bool isPlaying();

private:
    double m_sampleRate;
    int m_samples;

    double m_step;
    double m_cur;

    double m_duration;
    double m_elapsed;

    bool m_isPlaying;

    std::vector<double> m_table;

    void generateTable();
    void increment();
};

#endif
