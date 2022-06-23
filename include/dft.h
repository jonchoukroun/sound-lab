#ifndef DFT_H
#define DFT_H

#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>

class DFT {
public:
    struct DFTParams {
        std::string filename;
        int samplesCount;
    };

    DFT();
    ~DFT() = default;

    void setup(const DFTParams &);

    // void storeSignal(std::vector<double> &signal);
    void storeSignal(double sample);

    void run();

private:
    // Samples in time domain
    int m_N;
    // DFT points
    int m_XN;

    // Time domain
    std::vector<double> m_signal;

    // Rectangular form
    std::vector<double> m_XR;
    std::vector<double> m_XI;

    // Polar form
    std::vector<double> m_XMag;
    std::vector<double> m_XTheta;

    std::ofstream m_f;

    void setupFile(std::string filename);
    void toPolar();
    void write();
};


#endif
