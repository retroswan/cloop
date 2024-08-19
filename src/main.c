#include <stdio.h>
#include <SDL2/SDL.h>
#include "Cloop/Cloop.h"

int main(void)
{
    SDL_Init(0);
    
    printf("Hello, world!\n");
    
    int frames = 0;
    while (frames < 3000) {
        Cloop();
        
        frames ++;
        
        if (frames % 250 == 0) {
            SDL_Log("Frame %d\n", frames);
        }
    }
    
    printf("Goodbye, world!\n");
    
    SDL_Quit();
    
    return 0;
}
