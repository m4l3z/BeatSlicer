#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include "SDL.h"
#include <math.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "../AudioObject.h"
#include "../LoadFile.h"


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
//Buttons DONE 
//Sliders DONE
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
}Mouse;

struct Button{
    char * name;
    SDL_Rect pos;
    SDL_Surface *img0;
    SDL_Surface *img1;
    SDL_Surface *current;
    int state;
}Button1;

struct Button CreateButton(char * name, int x, int y, int w, int h, SDL_Surface * enabled, SDL_Surface *idle)
{
    struct Button button;
    button.name = name;
    button.pos.x =x;
    button.pos.y =y;
    button.pos.w =w;
    button.pos.h =h;
    button.img0 = idle;
    button.img1 = enabled;
    button.current = button.img0;
    button.state =0;
    return button;
}

int inButton(struct Button button, int x, int y)
{
    if( x >= button.pos.x && x <= button.pos.x + button.pos.w && y >= button.pos.y && y <= button.pos.y + button.pos.h) return 1;
    else return 0;
}

struct Slider{
    char * name;
    SDL_Rect pos, headpos;
    int x;
    SDL_Surface * back;
    SDL_Surface *head;
    int state;
}Slider1;

struct Slider CreateSlider(char * name, int x, int y, int w, int h, SDL_Surface * back, SDL_Surface *head)
{
    struct Slider slider;
    slider.name = name;
    slider.state = 0;
    slider.pos.x = x;
    slider.pos.y = y;
    slider.pos.w = w;
    slider.pos.h = h;
    slider.back = back;
    slider.head = head;
    slider.headpos.x =x+ 1;
    slider.headpos.y =y+ 80;
    slider.headpos.w = 20;
    slider.headpos.h =  20;
    return slider;
}

int inSlider(struct Slider slider, int x, int y)
{
    if( x >= slider.pos.x && x <= slider.pos.x + slider.pos.w && y >= slider.pos.y +slider.headpos.h/2 && y <= slider.pos.y + slider.pos.h - slider.headpos.h/2) return 1;
    else return 0;
}
 


struct Knob {
    char * name;
    SDL_Rect pos;
    double angle;
    int state;
    SDL_Surface * back;
    SDL_Surface * head;
}Knob1;

struct Knob CreateKnob (char * name, int x, int y, int w, int h, SDL_Surface * back, SDL_Surface *head)
{
    struct Knob knob;
    knob.name = name;
    knob.angle = 90;
    knob.pos.x = x;
    knob.pos.y = y;
    knob.pos.w = w;
    knob.pos.h = h;
    knob.back = back;
    knob.head = head;
    knob.state =0;
    return knob;
}

int inKnob(struct Knob knob, int x, int y)
{
    if( x >= knob.pos.x && x <= knob.pos.x + knob.pos.w && y >= knob.pos.y && y <= knob.pos.y + knob.pos.h) return 1;
    else return 0;
}

struct Waveform {
    char * name;
    SDL_Surface * back; 
    SDL_Surface * front; 
    struct AudioObject  object;
    SDL_Surface *  colour;
    SDL_Rect pos, blit;
}Waveform1;


struct Waveform CreateWaveform(char *name, int x, int y, int w, int h, SDL_Surface *back )
{
    struct Waveform waveform;
    waveform.name = name;
    waveform.back = back;
    waveform.colour = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0); 
    SDL_FillRect(waveform.colour, &waveform.colour->clip_rect, SDL_MapRGB(waveform.colour->format,34,209,65));
    
    waveform.object = LoadFile("../sample.wav");

    int step = waveform.object.size/400;
    Uint32 *pixel;
    for(int i = 0; i < w; i++)
    {
        waveform.pos.x = i;
        waveform.pos.y = 75 - (75*waveform.object.stream[i*step]);
        SDL_BlitSurface(waveform.colour, NULL, back, &waveform.pos);
        if (waveform.pos.y <=75) {
            for (int j = 75; j>=waveform.pos.y; j--) {
                     waveform.blit.y = j;
                     waveform.blit.x = i;
                     SDL_FillRect(waveform.colour, &waveform.colour->clip_rect, SDL_MapRGB(waveform.colour->format,34 ,209- 1.8*j ,65 ));

                     SDL_BlitSurface(waveform.colour, NULL, back, &waveform.blit);
            }
        }
        else if (waveform.pos.y > 75)
        {
            for (int j = 75; j<=waveform.pos.y; j++) {
                waveform.blit.y = j;
                waveform.blit.x = i;
                     SDL_FillRect(waveform.colour, &waveform.colour->clip_rect, SDL_MapRGB(waveform.colour->format,34 ,209+ 1.8*j ,65 ));
                SDL_BlitSurface(waveform.colour, NULL, back, &waveform.blit);
        }
        }
                    
       
        }

    SDL_Flip(back);
    waveform.pos.x = x;
    waveform.pos.y = y;
    waveform.pos.w = w;
    waveform.pos.h = h;
   
    //
    return waveform;
}

#endif  










