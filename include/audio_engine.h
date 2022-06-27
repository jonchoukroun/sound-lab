#pragma once

#include <array>
#include <SDL2/SDL.h>
#include <vector>
// #include "instrument.h"
#include "noise.h"
#include "settings.h"
#include "sine.h"

using std::array;
using std::vector;

class AudioEngine
{
public:
    AudioEngine() = default;
    ~AudioEngine();

    void updateSettings(Settings *);

    bool initialize();

    // void setInstrument(Noise *);
    void setInstrument(Sine *);

    void start();
    void stop();
    bool isPlaying();

    SDL_AudioDeviceID getAudioDevice();

private:
    Settings *m_settings;

    // Noise *m_noise;
    Sine *m_sine;

    SDL_AudioDeviceID m_deviceId = 0;
    SDL_AudioSpec m_receivedSpec {};

    bool m_playing = false;

    static void audioCallback(void *userdata, Uint8 *stream, int len);
    void fillBuffer(const Uint8* const stream, int len);
};
