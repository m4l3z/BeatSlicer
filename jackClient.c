// Based on OpenAvTutorials , Thanks Harry !!

//m4l3z's trial and mistakes for a beatslicer

#include <stdio.h>
#include <unistd.h>
#include <jack/jack.h>
#include <math.h>
#include <sndfile.h>
#include <malloc.h>
#include <jack/midiport.h>
#include <string.h>
//#include "struct.h"
#include "time.h"
#include "LoadFile.h"
#include "AudioObject.c"
#include "Slice.c"
// declare two "jack_port_t" pointers, which will each represent a port
// in the JACK graph (ie: Connections tab in QJackCtl)
jack_port_t* inputPort = 0;
jack_port_t* outputPortL = 0;
jack_port_t* outputPortR = 0;
// this function is the main audio processing loop, JACK calls this function
// every time that it wants "nframes" number of frames to be processed.
// nframes is usually between 64 and 256, but you should always program
// so that you can work with any amount of frames per process() call!
int process(jack_nframes_t nframes, void* emptyshell)
{
  // this is a little tricky, port_get_buffer() will return a pointer to
  // the data that we will use, so cast it to (float*), so that we
  // can use the data as floating point numbers. JACK will always pass
  // floating point samples around, the reason that we have to cast it
  // ourselves is so that it could be changed in the future... don't worry
  // about it too much.
  jack_midi_event_t in_event;

  float* inputBuffer = (float*)jack_port_get_buffer ( inputPort , nframes);
  float* outputBufferL= (float*)jack_port_get_buffer ( outputPortL, nframes);
  float* outputBufferR= (float*)jack_port_get_buffer ( outputPortR, nframes);

  //Object1.pos+= nframes;
  // this is the intresting part, we work with each sample of audio data
  //struct Slice *ptr  = EmptySlice.next;
  current =  &EmptySlice;
  jack_nframes_t event_count = jack_midi_get_event_count(inputBuffer);
  // one by one, copying them across. Try multiplying the input by 0.5,
  // it will decrease the volume...
  for ( int i = 0; i < (int) nframes; i++)
  {
    if(event_count > 0)
    {
    jack_midi_event_get(&in_event, inputBuffer, i);
    printf("Type (159 = NOTEON, 143 = NOTEOFF) : %i , Note : %i, Velocity : %i \n", in_event.buffer[0],
            in_event.buffer[1], in_event.buffer[2]);
    
    current =  &EmptySlice;
    while(current->next != NULL)
            {
                if(in_event.buffer[1] == current->next->key )
                {

                        if (current->next->isPlaying == 0 && in_event.buffer[0] == 159)
                        {
                            current->next->isPlaying =1;
                        }

                       
        }
                current= current->next;
    }
    

  }
    event_count = 0;
  } 
    // copy data from input to output. Note this is not optimized for speed!

    //Check in slice collection which one are playing and add those to the buffer 
    current  = &EmptySlice;
    for (int i = 0; i < (int) nframes; i++)
    {
    while(current->next != NULL)
        {
            if(current->next->isPlaying==1 && current->next->pos < current->next->length)
        {
            outputBufferL[i] = current->next->stream[i+current->next->pos];
            outputBufferR[i] = current->next->stream[i+current->next->pos];
            current->next->pos++;
        }
            else 
           {
               current->next->isPlaying =0;
               current->next->pos=0;
           }
            
        current = current->next;
        }
    //outputBufferL[i] = sample1[i]; 
    //outputBufferR[i] = sample1[i]; 
    
    }
 
    printf("\n pos : %i \n", *&EmptySlice.next->pos);
  
  return 0;
}





int main(int argc, char * argv[])
{
  printf("\n ** BeatSlicer Engine Test** \n");

  printf("Enter the sample path: \n"); 
  char path[256];
  scanf("%s", path);
  
  Object1 = LoadFile(path);
  
  //test slice create
  //SliceCreate( Object1, "forward", 0, 144000);
  //SliceCreate( Object1, "forward", 144000, 144000);
  //SliceCreate( Object1, "forward", 288000, 144000);
  //SliceCreate( Object1, "forward", 432000, 144000);
  struct Slice *current  =  malloc(sizeof(struct Slice));

  struct Slice *ptr = &EmptySlice; 
  EmptySlice.index = 0;
  EmptySlice.length =0;
  EmptySlice.playmode = "forward";
    

  //printf("%i", sizeof(Object1.stream[2]) * sizeof(float));
  SliceAutoSlice(Object1, "forward", 4);
    while(ptr->next != NULL)
        {
            ptr->next->pos = 0;
            ptr = ptr->next;
        }
  ptr = &EmptySlice; 

  while(ptr != NULL)
  {
        printf("Slice #%i, of size %i at pos %i with mode %s and key %i \n", ptr->index, ptr->length,ptr->pos, ptr->playmode, ptr->key);
        ptr = ptr->next;
  }
    //printf("test %i", EmptySlice.next->length);
  // create a JACK client and activate
  jack_client_t* client = jack_client_open ("NoLoveDeepSlice",
                                            JackNullOption,
                                            0,
                                            0 );
  printf("\n *Jack Client Created\n");

  // register the process callback : JACK "calls us back" when there is
  // work to be done, and the "process" function does that work.
  jack_set_process_callback  (client, process , 0);
  
  // register two ports, one input one output, both of AUDIO type
  inputPort = jack_port_register ( client,
                                    "input",
                                    JACK_DEFAULT_MIDI_TYPE,
                                    JackPortIsInput,
                                    0 );
  
  outputPortL = jack_port_register ( client,
                                    "outputL",
                                    JACK_DEFAULT_AUDIO_TYPE,
                                    JackPortIsOutput,
                                    0 );
  
  outputPortR = jack_port_register ( client,
                                    "outputR",
                                    JACK_DEFAULT_AUDIO_TYPE,
                                    JackPortIsOutput,
                                    0 );
  
  // activate the client, ie: enable it for processing
  jack_activate(client);
  printf("%i \n", Object1.pos); 
  // pause for 30 seconds, letting process() do it's thing
  sleep(300);
  
  // tell JACK to stop processing the client
  jack_deactivate(client);
  
  // close the client
  jack_client_close(client);
  
  return 0;
}

