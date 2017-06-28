#include <stdio.h>
#include <malloc.h>
#include "AudioObject.h"

//Methods

float * GenerateSample(struct AudioObject Object, int nframes)
    {
        float * Sample = malloc(nframes * sizeof(float));
        int i =0; 
        for(i =0; i <= nframes; i++) 
            Sample[i] = 0;
            //Return silence test
    
        if(Object.pos + nframes < Object.size) {
            for(i=0; i<nframes; i++) {
                Sample[i] = Object.stream[i+Object.pos];
             }
        }
    return Sample; 
    }




