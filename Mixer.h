#include <stdio.h>
#include "Slice.h" 

struct Mixer { 
    int voices;
    float volume;
    float * streamR;
    float * streamL;
}Mixer1;


struct Mixer MixerUpdate(int nframes) {
    //Clean mixer stream
    struct Mixer mixer;
    mixer.voices =0;
    mixer.volume = 1;
    mixer.streamR = mixer.streamL = malloc(sizeof(float)*nframes);

    for(int i =0; i<nframes; i++)
    {
        mixer.streamR = mixer.streamL = 0;
    }

    //Find number of voices playing 
    struct Slice *currentS;
    struct Playback *currentP;
    currentS  = &EmptySlice;
    currentP = &currentS->next->playback;
    while(currentS->next != NULL)
        {
            while(currentP->next != NULL) 
                {
                    if(currentP->state != "playing")
                    {
                        mixer.voices++;
                    }
                    currentP = currentP->next;
                }
            currentS = currentS->next;
        }

    //copy all the playbacks with their coefficients
    while(currentS->next != NULL)
        {
            while(currentP->next != NULL) 
                {
                    if(currentP->state != "playing")
                    {
                        for( int i =0; i < nframes; i++)
                        {
                            mixer.streamR[i] = mixer.streamL[i] = (SliceVolume(currentS->next, currentP->pos)/mixer.voices) *  currentS->next->stream[currentP->pos];
                            currentP->pos++;
                        }
                    }
                    currentP = currentP->next;
                }
            currentS = currentS->next;
        }
    

    //return the Mixer
    return mixer;
}
