#ifdef MIDI_H
#define MIDI_H

#include <stdio.h>
#include <malloc.h>

struct Midi_Event {
    int note;
    int velocity;
    int type;
    int channel;
}

char * MidiNoteToNote(int note);
int NoteToMidiNote(char * note);


#endif 
