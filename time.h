#include <stdio.h>

//convert the number of beats at a certain bpm to a time period
double BPM_to_time (float BPM, float nbeats)
{
    return (double) BPM/60 * nbeats;
}

//Convert a time period in a number of frames 
int time_to_frame(float time, int samplerate)
{
    return time * samplerate;
}
