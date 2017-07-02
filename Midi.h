#ifndef MIDI_H
#define MIDI_H

#include <stdio.h>
#include <malloc.h>
#include <jack/midiport.h>

struct Midi_Event {
    int note;
    int velocity;
    char * type;
    int channel;
};

struct Midi_Event DataToMidiEvent( jack_midi_event_t in_event)
{
    struct Midi_Event midi_event;
        if (in_event.buffer[0]<144){

            midi_event.type = "NOTE_OFF";
            midi_event.channel = in_event.buffer[0] - 127;
        }
        else if (in_event.buffer[0]>=144)
        {
            midi_event.type = "NOTE_ON";
            midi_event.channel = in_event.buffer[0] - 143;
        }
            midi_event.note = in_event.buffer[1];
            midi_event.velocity= in_event.buffer[2];

    return midi_event;
}

int MidiTrigger(struct Midi_Event midievent)
{
    struct Slice* currentS = &EmptySlice;
    struct Playback * currentP;
    while(currentS->next != NULL)
        {
            currentP = &currentS->next->playback;
           if (currentS->next->key == midievent.note)
            {
                int playbackleft = 1; 
                while(playbackleft) 
                    {
                        if(currentP->state == "playing" && midievent.type == "NOTE_ON")
                        {
                            
                            if(currentS->next->playmode == "FW_S") SliceStartPlayback(currentS->next);
                            if(currentS->next->playmode == "FW_P") currentP->pos = 0;
                            if(currentS->next->playmode == "FW_U") currentP->state = "playing";
                            
                        }
                        else if (currentP->state =="playing" && midievent.type == "NOTE_OFF")
                        {
                            if(currentS->next->playmode == "FW_P") 
                                {
                                    currentP->pos =0 ;
                                    currentP->state = "done";
                                }
                            if(currentS->next->playmode == "FW_U")
                            {
                                currentP->state = "paused";
                            }

                        }
                        else if (currentP->state =="paused" && midievent.type == "NOTE_ON")
                        {
                            if(currentP->pos < currentS->next->length)
                            {
                                currentP->state = "playing";
                            }
                            else
                            {
                                currentP->state = "done";
                                currentP->pos = 0;
                            }
                        }
                        else if (currentP->state == "done" && midievent.type == "NOTE_ON")
                        {
                            if(currentS->next->playmode == "FW_S") SliceStartPlayback(currentS->next);
                            if(currentS->next->playmode == "FW_P" || currentS->next->playmode == "FW_U"){
                                currentP->pos = 0;
                                currentP->state ="playing";}
                            
                        }
                        if(currentP->next == NULL) playbackleft=0;
                        else{
                        currentP = currentP->next;
                        }
                        printf("Slice at %i , mode %s and first playback state %s \n", &currentS->next,currentS->next->playmode, currentP->state); 
                    }
                }
            currentS = currentS->next;
        }
    
    //
    return 0;
}
 
#endif
