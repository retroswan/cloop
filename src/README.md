# Cloop

Tiny gameloop library in C &amp; SDL.

## Build

First, make sure you copy `example.env` to `.env` and make any changes necessary. If you have any special conditions (like wanting to use a specific compiler rather than the `cc` command), check the Makefile for which parameters to add to the `.env` file.

Then, try one of these commands:

```bash
# Defaults to `make debug`
make

# Makes a debug build of the library in `./bin/Debug`
# Also builds a test application
make debug

# Makes a release build of the library in `./bin/Release`
# Also builds a test application
make release
```

## Using It In Your Application

Here is a simple game loop with Cloop:

```c
#include <Cloop/Cloop.h>

int main(void)
{
    // This application doesn't need any SDL init flags
    // But your game probably does!
    SDL_Init(0);
    
    // `1` to use fuzzy timing. Read below for more info
    // NOTE: if you forget to initialize, it will behave unexpectedly!
    Cloop_Init(1);
    
    while (1) {
        // SLEEP is probably the timer you want
        // Read below for more info
        Cloop_Run(CLOOP_TIMING_SLEEP);
        
        // Do all of your game stuff in here!
        MyGameLogic();
    }
    
    SDL_Quit();
    
    // No need to quit Cloop, it doesn't allocate memory!
}
```

Build with a command like this:

```bash
cc -c main.c -o main.o -I/your/directory/cloop/include `sdl2-config --cflags`
cc main.o -o main -L/your/directory/cloop/bin` -lcloop `sdl2-config --libs`
```

## Questions

### What is Fuzzy Timing?

When initializing Cloop, you provide a value for whether or not to use Fuzzy Timing:

```c
// `1` for yes, `0` for no
Cloop_Init(1);
```

But what is it?

For the best answer, see Tyler Glaiel's excellent article [How to make your game run at 60fps](https://medium.com/@tglaiel/how-to-make-your-game-run-at-60fps-24c61210fe75).

In this article, he recounts how he resolved a frame stutter every 1000 frames:

> Recently when reviewing my timer code I noticed something odd. The accumulator was drifting, every frame would take a little bit longer than 1/60th of a second, so periodically the game would think its a frame behind and do a double update. It turns out my current monitor is 59.94hz instead of 60hz. This meant that once every 1000 frames, it would need to do a double update to “catch up”. Simpleish fix though, instead of having the range of acceptable framerates be 60 to 62, you just make it 59 to 61 instead.

Passing a `1` to `Cloop_Init` enables Fuzzy Timing.

### What Do The Different Loop Timings Do?

`NONE` will do nothing. Your game will only run at a specific framerate if vsync is applicable &amp; enabled for the application on the end user's device.

`BURN_CPU` will utilize the CPU constantly to determine if the next frame is ready. This is the most precide method, but will utilize more resources than you probably want.

`SLEEP` **is the preferred method.** It will utilize the OS's sleep timer to save CPU resources until the next frame is ready. Note that it does not sleep for e.g. 16ms, but rather for 1ms, then checks if the next frame is ready & repeats a 1ms sleep until it is. This is because OS sleep is not predictable &amp; will last *at least* as long as specified; it could potentially last longer &amp; cause an imprecise game loop.
