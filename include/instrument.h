#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <iostream>
#include <string>
#include "settings.h"

class Instrument
{
public:
    Instrument(Settings &);

    const Settings & settings() const;

    virtual double processAudio() = 0;

private:
    Settings &m_settings;
};

#endif
