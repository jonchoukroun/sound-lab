#include <iostream>
#include "audio_engine.h"

using std::cout;
using std::endl;

const double GAIN = 25000.0;

AudioEngine::~AudioEngine()
{
    SDL_CloseAudioDevice(m_deviceId);
}

void AudioEngine::updateSettings(Settings *s)
{
    m_settings = s;
    initialize();
}

bool AudioEngine::initialize()
{
    SDL_AudioSpec desiredSpec;
    desiredSpec.freq = m_settings->sampleRate();
    desiredSpec.format = AUDIO_S16;
    desiredSpec.channels = m_settings->channelCount();
    desiredSpec.samples = m_settings->sampleCount();
    desiredSpec.callback = &audioCallback;
    desiredSpec.userdata = this;

    if (m_deviceId != 0) SDL_CloseAudioDevice(m_deviceId);

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

// void AudioEngine::setInstrument(Noise *n)
// {
//     m_noise = n;
// }

// void AudioEngine::setInstrument(Sine *s)
// {
//     m_sine = s;
// }

void AudioEngine::setInstrument(Instrument *i)
{
    m_instrument = i;
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
        double y = m_instrument->processAudio();
        out[i] = GAIN * y;
    }
}
