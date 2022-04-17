#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <array>
#include <SDL2/SDL.h>
#include <vector>
#include "instrument.h"

using std::array;
using std::vector;

class AudioEngine
{
public:
    AudioEngine(Instrument &);
    ~AudioEngine();

    bool initialize();

    void start();
    void stop();
    bool isPlaying();

    SDL_AudioDeviceID getAudioDevice();

private:
    Instrument &m_instrument;

    static const int m_sampleRate = 44100;
    static const int m_sampleSize = 1024;
    static const int m_channels = 1;

    SDL_AudioDeviceID m_deviceId = 0;
    SDL_AudioSpec m_receivedSpec {};

    static constexpr double m_step = 1000.0 / (double)m_sampleRate;
    bool m_playing = false;
    double m_elapsed = 0.0;

    static void audioCallback(void *userdata, Uint8 *stream, int len);
    void fillBuffer(const Uint8* const stream, int len);
};

#endif
