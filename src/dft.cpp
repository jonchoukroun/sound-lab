#include "dft.h"

#define SAMPLE_RATE 44100

using std::cout;
using std::endl;

DFT::DFT()
{
    cout << "DFT initialized" << endl;
}

void DFT::setup(const DFTParams &p)
{
    m_N = p.samplesCount;
    m_XN = (m_N / 2) + 1;

    m_XR.resize(m_XN);
    std::fill(m_XR.begin(), m_XR.end(), 0);
    m_XI.resize(m_XN);
    std::fill(m_XI.begin(), m_XI.end(), 0);
    m_XMag.resize(m_XN);
    std::fill(m_XMag.begin(), m_XMag.end(), 0);
    m_XTheta.resize(m_XN);
    std::fill(m_XTheta.begin(), m_XTheta.end(), 0);

    setupFile(p.filename);

    cout << "DFT set up " << m_N << " " << m_XN << endl;
}

// void DFT::storeSignal(std::vector<double> &signal)
// {
//     m_signal = signal;

//     cout << "DFT signal stored (vector)" << endl;
// }

void DFT::storeSignal(double s)
{
    m_signal.push_back(s);
}

void DFT::run()
{
    for (auto k = 0; k < m_XN; ++k) {
        for (int i = 0; i < m_N; ++i) {
            m_XR[k] = m_XR[k] + m_signal[i] * cos(2 * M_PI * k * i / m_N);
            m_XI[k] = m_XI[k] + m_signal[i] * cos(2 * M_PI * k * i / m_N);
        }
    }
    toPolar();
    write();

    cout << "DFT complete" << endl;
}

void DFT::setupFile(std::string f)
{
    m_f.open(f);
    m_f << "Signal,,,DFT\nN,Amplitude,,Freq,M,theta\n";
}

void DFT::toPolar()
{
    for (auto i = 0; i < m_XN; ++i) {
        m_XMag[i] = sqrt(pow(m_XR[i], 2) + pow(m_XI[i], 2));
        m_XTheta[i] = atan(m_XI[i] / m_XR[i]);
    }

    cout << "DFT converted to polar" << endl;
}

void DFT::write()
{
    for (auto i = 0; i < m_N; ++i) {
        m_f << i << "," << m_signal[i] << ",,";
        if (i < m_XN) {
            // auto bin = ((SAMPLE_RATE / 2) / m_XN);
            m_f << i << "," << m_XMag[i] << "," << m_XTheta[i];
        }
        m_f << "\n";
    }

    cout << "DFT written to csv" << endl;
}
