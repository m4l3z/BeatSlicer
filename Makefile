all: jackClient.c 
	     gcc -Wall -g -o main jackClient.c -lm -ljack -lsndfile 
