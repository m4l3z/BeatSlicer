#include <stdio.h>
#include <malloc.h>
#include "Slice.h" 


char * MidiNoteToNote(int note)
{
}

int NoteToMidiNote(char * note)
{
}

int MidiTrigger( struct Midi_Event midi_event)
{
    struct Slice* currentS = &EmptySlice;
    struct Playback * currentP = &currentS->next->playback;
    
    while(currentS->next != NULL)
        {
            if (currentS->next->key == midi_event.note)
            {
                while(currentP->next != NULL) 
                    {
                        if(currentP->state == "playing" && midi_event.type == "NOTE_ON")
                        {
                            switch(currentS->next->playmode)
                            {
                                case "FW_S":
                                    SliceStartPlayback(currentS->next);
                                case "FW_P":
                                    currentP->pos = 0;
                                case "FW_U":
                                    currentP->state = "paused";
                            }
                        }
                        else if (currentP->state =="playing" && midi_event.type == "NOTE_OFF")
                        {
                            switch(currentS->next->playmode)
                            {
                                case "FW_S":
                                    //
                                case "FW_P":
                                    currentP->pos = 0;
                                    currentP->state = "done";
                                case "FW_U":
                                    currentP->state = "paused";
              
                            }
                        }
                        else if (currentP->state =="paused" && midi_event.type == "NOTE_ON")
                        {
                            currentP->state == "playing";
                        }
                        else if (currentP->state == "done" && midi_event.type == "NOTE_ON")
                        {
                            switch(currentS->next->playmode)
                            {
                                case "FW_S":
                                    SliceStartPlayback(currentS->next); 
                                case "FW_P":
                                    currentP->pos = 0;
                                    currentP->state = "playing";
                                case "FW_U":
                                    currentP->state = "playing";
                            }
                        }
                     
                    }
                    currentP = currentP->next;
                }
            currentS = currentS->next;
        }
    
    //
    return 0;
}
