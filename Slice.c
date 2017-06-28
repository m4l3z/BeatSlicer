#include <stdio.h>
#include <malloc.h>
#include "Slice.h"
#include "time.h"
//Methods for Slice

int SliceCreate( struct AudioObject Object, char * mode, int Pos, int Size, int key)
{
    int i;
   
    struct Slice *next = &EmptySlice;
    struct Slice *previous = EmptySlice.previous;
    
    int index=0;
    //Find the last slice
    while (next->next != NULL) {
       next = next->next; 
       previous = next;
       index++;
    }

    //Allocate memory
    next->next = (struct Slice*) malloc(sizeof(struct Slice));
    //Copy Data
    next->next->length = Size; 
    next->next->playmode = mode;
    next->next->pos= 0;
    next->next->isPlaying = 0; 
    next->next->previous= next;
    next->next->next= NULL; 
    next->next->index = index +1 ;
    next->next->source = Object; 
    next->next->key = key;
    next->next->stream = malloc(Size * sizeof(float));
    for(i=0; i<Size; i++)
    {
    
        next->next->stream[i] = Object.stream[Pos+i] ;
    }
    
    //Initialize basic values for envelope 
    next->next->envelope.attack_t = next->next->length*0.4;
    next->next->envelope.decay_v  = 0.85; 
    next->next->envelope.decay_t = next->next->length*0.5; 
    next->next->envelope.sustain_v = 0.8;
    next->next->envelope.sustain_t = next->next->length*0.6; 
    next->next->envelope.release_t = next->next->length*0.7; 


    return 0;


}

int SliceDelete(int index)
{
    int found = 1;
    struct Slice *next =  &EmptySlice;

    while(next->next != NULL) {
        if (next->next->index == index)
        {
            next->next = next->next->next;
            next->next->next->previous = next->next->previous; 
            free(next->next);
            found = 0;
    }
        next= next->next;

    }

    return found;
}

int SliceResize(int index, int pos, int size)
{
    int found = 1;
    struct Slice *next =  &EmptySlice;
    
    while(next->next !=NULL) {
        if (next->next->index == index)
        {
            int i;
            next->next->stream = malloc(size * sizeof(float));
            for(i =0; i<size; i++) 
            {
                next->next->stream[i] = next->next->source.stream[pos+i];
            }
            found = 0;

           }

    }
        return found;
}

int SliceAutoSlice( struct AudioObject Object, char * mode, int div)
{
   int i=0;
   
   while(i<div)

   {
       SliceCreate(Object, mode, (Object.size/div) * i, (int) Object.size/div, 60+i);
       i++;
   }
   return 0;
}

float * SliceGenerateSample(struct Slice * slice, int nframe, int speed)
{
    float * stream = malloc(sizeof(float)*nframe);
    int i;
    if(slice->pos + nframe < slice->length)
    {
    for(i=0; i<nframe; i++)
    {
        stream[i]=slice->stream[i + slice->pos];
    }
    slice->pos+=nframe;
    }
    else {
    slice->pos = 0;
    for(i=0; i<nframe;i++)
    {
        stream[i]=0;
    }

    }

    return stream;
}


float SliceVolume(struct Slice * slice)
{
    if (slice->pos >= 0 && slice->pos < slice->envelope.decay_t)
    {
        return (slice->envelope.decay_v) * (slice->pos / slice->envelope.attack_t) ;
    }
    
    if (slice->pos >= slice->envelope.decay_t && slice->pos < slice->envelope.sustain_t)
    {
        return (slice->envelope.decay_v) - (slice->envelope.decay_v - slice->envelope.sustain_v)*((slice->pos-slice->envelope.attack_t)/slice->envelope.decay_t);  
    }

   if ( slice->pos >= slice->envelope.sustain_t && slice->pos < slice->envelope.release_t)
   {
       return slice->envelope.sustain_v;
   }
   if ( slice->pos >= slice->envelope.release_t && slice-> pos <= slice->length )
   {
       return slice->envelope.sustain_v - (slice->envelope.sustain_v * ((slice->pos- slice->envelope.release_t)/(slice->length - slice->envelope.release_t)));
}
return 0;
}
