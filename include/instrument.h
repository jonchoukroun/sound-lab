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

    void trigger();

    // TODO: change to block processing
    virtual double getSample() = 0;

private:
    Settings &m_settings;

    bool m_playing;
};

#endif
