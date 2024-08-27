#include <SDL2/SDL.h>
#include <Cloop/Cloop.h>

int main(void)
{
    SDL_Init(0);
    
    SDL_Log("Hello, world!\n");
    
    int frames = 0;
    
    Uint64 begin, end;
    begin = SDL_GetPerformanceCounter();
    
    Cloop_Init(1);
    
    const int framesLimit = 3000;
    while (frames < framesLimit) {
        Cloop_Run(CLOOP_TIMING_SLEEP);
        
        frames++;
        
        if (frames % 250 == 0) {
            SDL_Log("Frame %d / %d\n", frames, framesLimit);
        }
    }
    
    end = SDL_GetPerformanceCounter();
    
    SDL_Log(
        "It took %1.10f seconds\n",
        ((float)(end - begin) / SDL_GetPerformanceFrequency())
    );
    
    SDL_Log("Goodbye, world!\n");
    
    SDL_Quit();
    
    return 0;
}
