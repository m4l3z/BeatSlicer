#include <stdio.h>
#include <sndfile.h> 
#include <malloc.h>
#include "AudioObject.h"

struct AudioObject LoadFile(char * path)
{
     struct AudioObject Object1;
     
     // Open sound file
     SF_INFO sndInfo;
     SNDFILE *sndFile = sf_open(path, SFM_READ, &sndInfo);
     
     if (sndFile == NULL) {
            fprintf(stderr, "Error reading source file '%s': %s\n", path, sf_strerror(sndFile));
            return Object1;
            }

     // Check format - 16bit PCM
     if (sndInfo.format != (SF_FORMAT_WAV | SF_FORMAT_PCM_16)) {
            fprintf(stderr, "Input should be 16bit Wav\n");
            sf_close(sndFile);
            return Object1;
            }

     // Check channels - mono
     if (sndInfo.channels != 1) {
            fprintf(stderr, "Wrong number of channels\n");
            sf_close(sndFile);
            return Object1;
            }


     // Allocate memory

     float *buffer = malloc(sndInfo.frames * sizeof(float));
     
     if (buffer == NULL) {
            fprintf(stderr, "Could not allocate memory for data\n");
            sf_close(sndFile);
            return Object1;
            }
     
     // Load data
     long numFrames = sf_readf_float(sndFile, buffer, sndInfo.frames);

     // Check correct number of samples loaded
     if (numFrames != sndInfo.frames) {
            fprintf(stderr, "Did not read enough frames for source\n");
            sf_close(sndFile);
            free(buffer);
            return Object1;
     }
     
     // Preparation of the Audio Object to return
     Object1.pos = 0;
     Object1.stream= buffer;
     Object1.size = sndInfo.frames;
    
     return Object1;
}

