#include "Cloop.h"
#include <SDL2/SDL_timer.h>

static Cloop_Timer Cloop_Accumulator = 0;
static Cloop_Timer Cloop_Framerate_Check = 0;
static Cloop_Timer Cloop_Framerate_Decrement = 0;
static Cloop_Timer Cloop_Previous = 0;

void Cloop_Init(char useFuzzyTiming)
{
    const int fuzziniess = useFuzzyTiming
        ? 1
        : 0;
    
    // Always 60 FPS
    Cloop_Framerate_Check = SDL_GetPerformanceFrequency() / 60 + fuzziniess;
    Cloop_Framerate_Decrement = SDL_GetPerformanceFrequency() / 60 - fuzziniess;
}

void Cloop_Run(Cloop_Timing timing)
{
    if (timing != CLOOP_TIMING_NONE) {
        while (Cloop_Accumulator < Cloop_Framerate_Check) {
            const Cloop_Timer current = SDL_GetPerformanceCounter();
            Cloop_Previous = Cloop_Previous
                ? Cloop_Previous
                : current;
            const Cloop_Timer delta = current - Cloop_Previous;
            Cloop_Previous = current;
            Cloop_Accumulator += delta;
            
            if (timing == CLOOP_TIMING_SLEEP) {
                SDL_Delay(1);
            }
        }
    }
    
    Cloop_Accumulator -= (Cloop_Framerate_Decrement > Cloop_Accumulator
        ? Cloop_Accumulator
        : Cloop_Framerate_Decrement);
}
