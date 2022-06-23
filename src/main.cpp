#include <iostream>
#include <SDL2/SDL.h>
#include "audio_engine.h"
#include "noise.h"
#include "sine.h"
#include "timer.h"

using std::cout;
using std::endl;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const double SAMPLE_RATE = 44100.0;
const int SAMPLE_SIZE = 1024;

static const double TICKS_PER_FRAME = 1000.0 / 60.0;

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;

bool init();

void close();

int main()
{
    if (!init()) return -1;

    bool quit = false;
    SDL_Event e;
    Timer fpsTimer;

    // Sine::Settings is {
    //     .sampleRate = SAMPLE_RATE,
    //     .sampleSize = SAMPLE_SIZE
    // };
    // Sine sine {is};

    // sine.setFrequency(480);

    Noise noise;

    // AudioEngine engine(sine);
    AudioEngine engine(noise);
    if (!engine.initialize()) return -1;

    while(!quit) {
        fpsTimer.start();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                        if (engine.isPlaying()) engine.stop();
                        quit = true;
                        break;

                    case SDLK_SPACE:
                        // sine.trigger();
                        noise.trigger();

                        if (engine.isPlaying()) engine.stop();
                        else engine.start();
                        break;

                    case SDLK_f:
                        // sine.toggleFilter();
                        // noise.toggleFilter();
                        break;
                }
            } else if (e.type == SDL_QUIT) {
                if (engine.isPlaying()) engine.stop();
                quit = true;
            }
        }
    }

    Uint32 ticks = fpsTimer.getTicks();
    if (ticks < TICKS_PER_FRAME) {
        SDL_Delay(TICKS_PER_FRAME - ticks);
    }
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cout << "Failed to initialize SDL! Error: " << SDL_GetError() << endl;
        return false;
    }

    gWindow = SDL_CreateWindow(
        "SoundLab",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (gWindow == NULL)
    {
        cout << "Failed to create Window! Error: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void close()
{
    SDL_Quit();
}
