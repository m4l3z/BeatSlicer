#include <stdio.h>
#include <malloc.h>
#include "Slice.h" 
#include "Midi.h"


int MidiTrigger(struct Midi_Event lomidievent)
{
    struct Slice* currentS = &EmptySlice;
    struct Playback * currentP = &currentS->next->playback;
    
    while(currentS->next != NULL)
        {
           if (currentS->next->key == midievent.note)
            {
                while(currentP->next != NULL) 
                    {
                        if(currentP->state == "playing" && midievent.type == "NOTE_ON")
                        {
                            if(currentS->next->playmode == "FW_S") SliceStartPlayback(currentS->next);
                            if(currentS->next->playmode == "FW_P") currentP->pos = 0;
                            if(currentS->next->playmode == "FW_U") currentP->state = "paused";
                            
                        }
                        else if (currentP->state =="playing" && midievent.type == "NOTE_OFF")
                        {
                            if(currentS->next->playmode == "FW_S") ;
                            if(currentS->next->playmode == "FW_P") currentP->pos =0 ;
                            if(currentS->next->playmode == "FW_U") currentP->state = "paused";

                        }
                        else if (currentP->state =="paused" && midievent.type == "NOTE_ON")
                        {
                            currentP->state == "playing";
                        }
                        else if (currentP->state == "done" && midievent.type == "NOTE_ON")
                        {
                            if(currentS->next->playmode == "FW_S") SliceStartPlayback(currentS->next);
                            if(currentS->next->playmode == "FW_P"){
                                currentP->pos = 0;
                                currentP->state ="playing";}
                            if(currentS->next->playmode == "FW_U") currentP->state = "playing";
                            
                        }
                     
                    }
                    currentP = currentP->next;
                }
            currentS = currentS->next;
        }
    
    //
    return 0;
}
