all: jackClient.c 
	     gcc -Wall -o main jackClient.c -lm -ljack -lsndfile 
