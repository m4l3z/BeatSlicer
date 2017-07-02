#include <stdio.h>
#include "Slice.h" 

struct Mixer { 
    int voices;
    float volume;
    float * streamR;
    float * streamL;
}Mixer1;


int MixerUpdate(struct Mixer *mixer, int nframes) {
    //Clean mixer stream
    //mixer = malloc(sizeof(struct Mixer));
    mixer->voices =0;
    mixer->volume = 1;
    mixer->streamR = malloc(sizeof(float)*nframes);
    mixer->streamL = malloc(sizeof(float)*nframes);
    /*
    for(int i =0; i<nframes; i++)
    {
        mixer->streamR[i] = mixer->streamL[i] = 0;
    }
    */
    //Find number of voices playing 
    struct Slice *currentS;
    struct Playback currentP;
    currentS  = &EmptySlice;
    while(currentS->next != NULL)
        {
            currentP = currentS->next->playback;
            int playbackleft=1;
            while(playbackleft) 
                {
                    if(currentP.state == "playing")
                    {
                        mixer->voices++;
                        printf("playing 1");
                    }
                    if(currentP.next ==NULL) playbackleft=0;
                    else currentP = *currentP.next;
                }
            currentS = currentS->next;
        }
    
    currentS  = &EmptySlice;
    currentP = currentS->next->playback;
    
    //copy all the playbacks with their coefficients
    while(currentS->next != NULL)
        {
            currentP = currentS->next->playback;
            int playbackleft=1;
            while(playbackleft)
                {
                    if(currentP.state == "playing")
                    {
                        for( int i =0; i < nframes; i++)
                        {
                            mixer->streamL[i] += (float) (SliceVolume(currentS->next, currentP.pos)/mixer->voices) *  currentS->next->stream[currentP.pos];
                            mixer->streamR[i] += (float) (SliceVolume(currentS->next, currentP.pos)/mixer->voices) *  currentS->next->stream[currentP.pos];
                            currentP.pos++;
                        }
                    }
                    if(currentP.next ==NULL) playbackleft=0;
                    else currentP = *currentP.next;
                }
            currentS = currentS->next;
        } 
    

    //return the Mixer
    return 0;
}
