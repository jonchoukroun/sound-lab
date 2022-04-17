#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <vector>
#include <cmath>

class Instrument
{
public:
    void initialize(double F, int N);
    void setFrequency(double f);

    void start();
    void stop();

    double getAmplitude();

    bool isPlaying();

private:
    double m_sampleRate;
    int m_samples;

    double m_step;
    double m_cur;

    bool m_isPlaying;

    std::vector<double> m_table;

    void generateTable();
};

#endif
