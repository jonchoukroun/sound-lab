#include <iostream>
#include "audio_engine.h"

using std::cout;
using std::endl;

const double GAIN = 25000.0;

AudioEngine::AudioEngine(Instrument &inst)
: m_instrument(inst)
{
    m_instrument.initialize(m_sampleRate, m_sampleSize);
}

AudioEngine::~AudioEngine()
{
    SDL_CloseAudioDevice(m_deviceId);
}

bool AudioEngine::initialize()
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
        return false;
    }

    return true;
}

void AudioEngine::start()
{
    cout << "Play" << endl;
    m_playing = true;
    SDL_PauseAudioDevice(m_deviceId, SDL_FALSE);
}

void AudioEngine::stop()
{
    cout << "Stop" << endl;
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
        if (m_instrument.isPlaying()) {
            output += GAIN * m_instrument.getSample();
        }
        out[i] = output;
        m_instrument.update(m_step);
    }
}
