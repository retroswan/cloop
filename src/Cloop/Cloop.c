#include "Cloop.h"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>

static Cloop_Timer Cloop_Accumulator = 0;
static Cloop_Timer Cloop_Framerate_Check = 0;
static Cloop_Timer Cloop_Framerate_Decrement = 0;
static Cloop_Timer Cloop_Previous = 0;

static inline void Cloop_Init_Maybe(void)
{
    if (
        Cloop_Framerate_Check == 0
        || Cloop_Framerate_Decrement == 0
        || 1
    ) {
        // Always 60 FPS
        Cloop_Framerate_Check = SDL_GetPerformanceFrequency() / 60;
        Cloop_Framerate_Decrement = SDL_GetPerformanceFrequency() / 60;
    }
}

static char Cloop_Repeat = 0;

void Cloop(void)
{
    // Initialize if we haven't yet
    Cloop_Init_Maybe();
    
    while (Cloop_Accumulator < Cloop_Framerate_Check) {
        Cloop_Repeat = 0;
        const Cloop_Timer current = SDL_GetPerformanceCounter();
        Cloop_Previous = Cloop_Previous
            ? Cloop_Previous
            : current;
        const Cloop_Timer delta = current - Cloop_Previous;
        Cloop_Previous = current;
        Cloop_Accumulator += delta;
        
        SDL_Delay(1);
    }
    
    if (Cloop_Repeat) {
        SDL_Log("Repeating!\n");
    }
    
    Cloop_Repeat = 1;
    
    Cloop_Accumulator -= (Cloop_Framerate_Decrement > Cloop_Accumulator
        ? Cloop_Accumulator
        : Cloop_Framerate_Decrement);
}
