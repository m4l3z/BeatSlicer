#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include "SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

//theme
//colors and stuff
//image files 

//zones
//
//
//


//Creations of the stuff I will need
//Waveform
//Mixer Histogram
//Buttons
//Sliders
//Knobs
//pop ups 
//drop down menus
//Log window
//sample list 
//tabs 
//leds
//volume meter 

struct Pos{
    int x;
    int y;
};

struct Button{
    char * name;
    SDL_Rect pos;
    SDL_Surface *img0;
    SDL_Surface *img1;
    int state;
}Button1;

struct Button  CreateButton(char * name, int x, int y, int w, int h, SDL_Surface * enabled, SDL_Surface *idle)
{
    struct Button button;
    button.name = name;
    button.pos.x =x;
    button.pos.y =y;
    button.pos.w =w;
    button.pos.h =h;
    button.img0 = idle;
    button.img1 = enabled;
    button.state =0;
    return button;
}
    
#endif  
















