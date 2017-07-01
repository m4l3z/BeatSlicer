#ifndef SLICE_H
#define SLICE_H

#include <stdio.h>
#include <malloc.h>
#include "AudioObject.h"


//Definition of Envelope

struct Envelope {
    float attack_t;
    float decay_v, decay_t;
    float sustain_v, sustain_t;
    float release_t;

};

struct Playback {
    char * state;
    int pos;
    struct Playback *next;

};

//Definition of Slice 

struct Slice {
    char * playmode; // Straight, reverse, 
    int pos;
    int length;
    int isPlaying;
    float * stream;
    struct Slice *next ;
    struct Slice *previous;
    struct Envelope envelope;
    int index;
    int key;
    struct AudioObject source;
    struct Playback playback;
}EmptySlice;


int SliceCreate( struct AudioObject Object, char * mode, int Pos, int Size, int key);
int SliceDelete(int index);
int SliceResize(int index, int pos, int size);
int SliceAutoSlice( struct AudioObject Object, char * mode, int div);
float * SliceGenerateSample(struct Slice * slice, int nframe, int speed);
float SliceVolume(struct Slice * slice);
int SliceStartPlayback(struct Slice * slice);


#endif

