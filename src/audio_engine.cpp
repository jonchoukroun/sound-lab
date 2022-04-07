#include <iostream>
#include "audio_engine.h"

using std::cout;
using std::endl;

AudioEngine::AudioEngine()
{
    SDL_AudioSpec desiredSpec;
    desiredSpec.freq = m_sampleRate;
    desiredSpec.format = AUDIO_S16;
    desiredSpec.channels = 1;
    desiredSpec.samples = m_sampleSize;
    desiredSpec.callback = &audioCallback;
    desiredSpec.userdata = this;

    m_deviceId = SDL_OpenAudioDevice(
        NULL,
        SDL_FALSE,
        &desiredSpec,
        &m_receivedSpec,
        0
    );
    if (m_deviceId == 0) {
        cout << "Failed to open audio device! Error: " << SDL_GetError() << endl;
    }
}

AudioEngine::~AudioEngine()
{
    SDL_CloseAudioDevice(m_deviceId);
}

void AudioEngine::start()
{
    m_playing = true;
    SDL_PauseAudioDevice(m_deviceId, SDL_FALSE);
}

void AudioEngine::stop()
{
    m_playing = false;
    SDL_PauseAudioDevice(m_deviceId, SDL_TRUE);

}

bool AudioEngine::isPlaying()
{
    return m_playing;
}

SDL_AudioDeviceID AudioEngine::getAudioDevice()
{
    return m_deviceId;
}

void AudioEngine::audioCallback(void *userdata, Uint8 *stream, int len)
{
    const auto engine = reinterpret_cast<AudioEngine *>(userdata);
    engine->fillBuffer(stream, len);
}

void AudioEngine::fillBuffer(const Uint8* const stream, int len)
{
    short *out = (short *)stream;
    for (unsigned long i = 0; i < (len / sizeof(short)); i++) {
        double output = 0.0;

        out[i] = output;
    }
}
