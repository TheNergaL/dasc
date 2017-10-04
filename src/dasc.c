#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
	size_t id, thread;
} drone;

typedef struct {
	int[]  airspace[ n ] [ m ] ;
} air;

void main(int argc, char* argv[]) {
	int count;
	pthread_t *dthreads; 
	if (argc == 0) { printf("Enter: %s n\n where n is the number of drones to place in the air. ", argv[0]); exit(1); }
	int num_drones = atoi(argv[1]); 	
	if (num_drones < 1 || num_drones > sizeof(int)) { printf("You must test at least one drone. ", argv[0]); exit(1); }
  	air *as = (air *)malloc(sizeof(air)*num_drones);
	dthreads=(pthread_t *)malloc(num_drones*sizeof(*dthreads));
	for (size_t i = 0; i < num_drones; i++) {
		as[count].n = count;
		as[count].m = count;
		pthread_create(&dtheads[count],NULL,... , ...);	
		  
 }
