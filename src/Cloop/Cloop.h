#pragma once

#define CLOOP_FUZZY 1

#include <SDL2/SDL_stdinc.h>

typedef enum Cloop_Timing
{
    CLOOP_TIMING_NONE,
    CLOOP_TIMING_BURNCPU,
    CLOOP_TIMING_SLEEP,
} Cloop_Timing;

typedef Uint64 Cloop_Timer;

void Cloop_Init(char useFuzzyTiming);
void Cloop_Run(Cloop_Timing timing);
