#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <array>
#include <SDL2/SDL.h>
#include <vector>
#include "noise.h"
#include "sine.h"

using std::array;
using std::vector;

class AudioEngine
{
public:
    AudioEngine(Sine &);
    // AudioEngine(Noise &);
    ~AudioEngine();

    bool initialize();

    void start();
    void stop();
    bool isPlaying();

    SDL_AudioDeviceID getAudioDevice();

private:
    // Noise &m_noise;
    Sine &m_sine;

    static const int m_sampleRate = 44100;
    static const int m_sampleSize = 1024;
    static const int m_channels = 1;

    SDL_AudioDeviceID m_deviceId = 0;
    SDL_AudioSpec m_receivedSpec {};

    bool m_playing = false;

    static void audioCallback(void *userdata, Uint8 *stream, int len);
    void fillBuffer(const Uint8* const stream, int len);
};

#endif
