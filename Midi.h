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

char * MidiNoteToNote(int note);
int NoteToMidiNote(char * note);
int MidiTrigger( struct Midi_Event midi_event);
 
