CC = gcc            #the compiler
CFLAGS = -g -Wall   #compiler flags

all: dcas

tuckerpo_proj1: dcas.c
				gcc dcas.c -o tuckerpo_proj1 -lpthread -lm  


clean: 	
	rm tuckerpo_proj1