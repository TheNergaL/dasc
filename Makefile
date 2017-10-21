CC = gcc
CFLAGS = -g -Wall -std=c99 -pthread	
all: tuckerpo_proj1

tuckerpo_proj1: src/dcas.c
		gcc -std=c99 src/dcas.c -o tuckerpo_proj1 -pthread


clean: 	
	rm tuckerpo_proj1
