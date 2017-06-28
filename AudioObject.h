#ifndef AUDIOOBJECT_H
#define AUDIOOBJECT_H

#include <stdio.h>
#include <malloc.h>

// Definition of Audio Objects 

struct AudioObject {
    float * stream;
    int pos;
    int size;
}Object1;


float * GenerateSample(struct AudioObject Object, int nframes);

#endif
