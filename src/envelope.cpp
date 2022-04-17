#include <cmath>
#include <fstream>
#include <iostream>
#include "envelope.h"

using std::cout;
using std::endl;

Envelope::Envelope(Settings &s)
: m_sampleRate(s.sampleRate)
, m_samples(s.sampleSize - 1)
, m_duration(s.attack + s.decay)
{
    setAttack(s.attack);
    setDecay(s.decay);
    setTargetRatioA(s.targetRatioA);
    setTargetRatioD(s.targetRatioD);

    cout << "Envelope initialized" << endl;
    cout << "attackRate = " << m_attackRate << endl;
    cout << "attackBase = " << m_attackBase << endl;
    cout << "attackCoef = " << m_attackCoef << endl;
    cout << "decayRate = " << m_decayRate << endl;
    cout << "decayBase = " << m_decayBase << endl;
    cout << "decayCoef = " << m_decayCoef << endl;
}

void Envelope::setAttack(double rate)
{
    m_attackRate = rate;
    m_attackCoef = calcCoef(m_attackRate, m_targetRatioA);
    m_attackBase = (1.0 + m_targetRatioA) * (1.0 - m_attackCoef);
}

void Envelope::setDecay(double rate)
{
    m_decayRate = rate;
    m_decayCoef = calcCoef(m_decayRate, m_targetRatioD);
    m_decayBase = -m_targetRatioD * (1.0 - m_decayCoef);
}

void Envelope::setTargetRatioA(double r)
{
    if (r < 0.000000001) {
        r = 0.000000001;
    }
    m_targetRatioA = r;
    m_attackCoef = calcCoef(m_attackRate, m_targetRatioA);
    m_attackBase = (1.0 + m_targetRatioA) * (1.0 - m_attackCoef);
}

void Envelope::setTargetRatioD(double r)
{
    if (r < 0.000000001) {
        r = 0.000000001;
    }
    m_targetRatioD = r;
    m_decayCoef = calcCoef(m_decayRate, m_targetRatioD);
    m_decayBase = -m_targetRatioD * (1.0 - m_decayCoef);
}

void Envelope::trigger()
{
    if (m_state == off) m_state = attack;
}

double Envelope::getDuration()
{
    return m_duration;
}

double Envelope::getAmplitude()
{
    switch (m_state) {
        case off:
            break;
        case attack:
            m_amplitude = m_attackBase + m_amplitude * m_attackCoef;
            if  (m_amplitude >= 1.0) {
                m_amplitude = 1.0;
                m_state = decay;
            }
            break;
        case decay:
            m_amplitude = m_decayBase + m_amplitude * m_decayCoef;
            if (m_amplitude <= 0.0) {
                m_amplitude = 0.0;
                m_state = off;
            }
            break;
    }
    return m_amplitude;
}

double Envelope::calcCoef(double rate, double targetRatio)
{
    auto x = (rate <= 0) ? 0.0 : std::exp(-std::log((1.0 + targetRatio) / targetRatio) / rate);
    cout << "x = " << x << endl;
    return x;
}
