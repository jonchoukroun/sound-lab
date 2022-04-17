#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <vector>

class Envelope
{
public:
    struct Settings {
        double sampleRate;
        int sampleSize;
        double attack;
        double decay;
        double targetRatioA;
        double targetRatioD;
    };

    enum EnvState {
        off = 0,
        attack,
        decay
    };

    Envelope(Settings &);
    ~Envelope() = default;

    void setAttack(double);
    void setDecay(double);
    void setTargetRatioA(double);
    void setTargetRatioD(double);

    void trigger();

    double getDuration();
    double getAmplitude();

private:
    double m_sampleRate;
    int m_samples;

    double m_attackRate;
    double m_decayRate;
    double m_duration;
    double m_attackCoef;
    double m_decayCoef;
    double m_attackBase;
    double m_decayBase;
    double m_targetRatioA;
    double m_targetRatioD;

    double m_amplitude = 0.0;
    EnvState m_state = off;

    double calcCoef(double rate, double targetRatio);
};

#endif
