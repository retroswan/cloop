#pragma once

#include <SDL2/SDL_stdinc.h>

/**
 * Different methods of running the game loop.
 */
typedef enum Cloop_Timing
{
    // Does nothing; will NOT run at 60fps without vsync!
    CLOOP_TIMING_NONE,
    // The most precise timer, but will utilize the CPU even while the game is
    // waiting for the next frame. SLEEP is preferred most of the time.
    CLOOP_TIMING_BURNCPU,
    // The preferred setting most of the time. Uses the OS sleep function to
    // wait for the next frame.
    CLOOP_TIMING_SLEEP,
} Cloop_Timing;

typedef Uint64 Cloop_Timer;

/**
 * Initializes the loop manager.
 *
 * Run this before starting your game!
 *
 * @param   char  useFuzzyTiming  whether to use Fuzzy Timing, as defined by
                                  Tyler Glaiel in his great Medium article:
                                  https://medium.com/@tglaiel/how-to-make-your-game-run-at-60fps-24c61210fe75
 */
void Cloop_Init(char useFuzzyTiming);

/**
 * Manages the game timer. Will hold up your application until it's time for the
 * next frame.
 *
 * @param   Cloop_Timing    timing  which timing method to use. SLEEP is
 *                          probably the one you want
 */
void Cloop_Run(Cloop_Timing timing);
