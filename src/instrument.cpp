#include "instrument.h"

using std::cout;
using std::endl;

Instrument::Instrument(Settings &s)
: m_settings(s)
{
    cout << "Instrument initialized" << endl;
}

const Settings & Instrument::settings() const
{
    return m_settings;
}
