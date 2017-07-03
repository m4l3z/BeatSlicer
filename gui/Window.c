#include <stdio.h>
#include "SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Window.h"

SDL_Surface *screen;
SDL_Event event;

int main(int argc, char *arvg[])
{
    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
    SDL_WM_SetCaption("Window","Window");
    SDL_Surface *idle, *enabled;
    idle = IMG_Load("idle.png");
    enabled = IMG_Load("enabled.png");
    Button1 = CreateButton("test", 200, 200, 50, 50, enabled, idle) ;
    int done = 0;
    while(!done)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                done =1;
            }
        }


        SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format,60,120,0));
        SDL_BlitSurface(Button1.img0, NULL, screen, &Button1.pos);
        SDL_Flip(screen);


    }
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
