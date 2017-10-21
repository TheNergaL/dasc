#include "../includes/map.h"
#include "../includes/drone.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void *action(void* drone){
	Keeper *k = (Keeper*)drone;
	Drone *d = k->drone;
	Map *m = k->map;
	
	controlTower(d,m);
	
	pthread_exit(NULL);
}

void *printer(void* map){
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = 100000000L;
	
	Keeper *k = (Keeper*)map;
	Map *m = k->map;
	
	sleep(.5);
	while(m->map[0][0].drone != k->count){
		printMap(m);
		nanosleep(&tim , &tim2);
	}
	
	pthread_exit(NULL);
}

int main(int argc,char *argv[]){
	int level = 3;
	int droneCount = 10;
	int buildings = 100;
	
	if (argc != 1){
		if (argc == 2){
			if(atoi(argv[1]) == 0){
				level = atoi(argv[1]);
				droneCount = 1;
				buildings = 0;
			}
			else if(atoi(argv[1]) == 1){
				level = atoi(argv[1]);
				droneCount = 10;
				buildings = 0;
			}
			else if(atoi(argv[1]) == 2){
				level = atoi(argv[1]);
				droneCount = 10;
				buildings = 2;
			}
			else if(atoi(argv[1]) == 3){
				level = atoi(argv[1]);
				droneCount = 10;
				buildings = 100;
			}
			else{
				printf("Wrong Arguments, please read README.\n");
				return 0;
			}
		}
		else if (argc == 3 && atoi(argv[2]) <= 250){
                        if(atoi(argv[1]) == 0){
                                level = atoi(argv[1]);
                                droneCount = atoi(argv[2]);
                                buildings = 0;
                        }
                        else if(atoi(argv[1]) == 1){
                                level = atoi(argv[1]);
                                droneCount = atoi(argv[2]);
                                buildings = 0;
                        }
                        else if(atoi(argv[1]) == 2){
                                level = atoi(argv[1]);
                                droneCount = atoi(argv[2]);
                                buildings = 2;
                        }
                        else if(atoi(argv[1]) == 3){
                                level = atoi(argv[1]);
                                droneCount = atoi(argv[2]);
                                buildings = 100;
                        }
                        else{
                                printf("Wrong Arguments, please read README.\n");
                                return 0;
                        }

		}
		else if(argc == 4 && atoi(argv[2]) <= 250 && atoi(argv[3]) <= 250){
                        if(atoi(argv[1]) == 0){
                                level = atoi(argv[1]);
                                droneCount = atoi(argv[2]);
                                buildings = atoi(argv[3]);
                        }
                        else if(atoi(argv[1]) == 1){
                                level = atoi(argv[1]);
                                droneCount = atoi(argv[2]);
                                buildings = atoi(argv[3]);
                        }
                        else if(atoi(argv[1]) == 2){
                                level = atoi(argv[1]);
                                droneCount = atoi(argv[2]);
                                buildings = atoi(argv[3]);
                        }
                        else if(atoi(argv[1]) == 3){
                                level = atoi(argv[1]);
                                droneCount = atoi(argv[2]);
                                buildings = atoi(argv[3]);
                        }
                        else{
                                printf("Wrong arguments, please read README.\n");
                                return 0;
                        }

		}
		else{
			printf("Wrong arguments, please read README.\n");
			return 0;
		}
	}



	srand(time(NULL));
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = 100000000L;
	
	pthread_t threads[droneCount+1];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	void *status;
	
	Map *m;
	Map map = createMap(0,0);
	m = &map;
	
	createBuilding(m,buildings);
	
	int i;
	
	Keeper k;
	k.map = m;
	k.count = droneCount;
	pthread_create(&threads[0], &attr, printer,(void*)&k);
	
	//Create Drones
	for(i = 1;i <= droneCount;i++){
		Drone *d = orderDrone(m,i);
		m->drones[i] = d;
		k.drone = m->drones[i];
		pthread_create(&threads[i], &attr, action,(void*)&k);
		nanosleep(&tim , &tim2);
		// sleep(1);
	}
	
	pthread_attr_destroy(&attr);
	
	//Wait for all drones to complete
	for(i = 1; i <=droneCount;i++){
		pthread_join(threads[i],&status);
	}
	
	pthread_join(threads[0],status);
	pthread_exit(NULL);
	return 0;
}