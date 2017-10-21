#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#define NUM_DRONES 10


pthread_mutex_t mtx;


typedef struct {
   int airport_x;
   int airport_y;
   int change_x;
   int change_y;
   char symbol;
   bool state;
} Drone;

char airspace[50][50];

Drone d0, d1, d2, d3, d4, d5, d6, d7, d8, d9;
Drone drone_arr[10] = {d0, d1, d2, d3, d4, d5, d6, d7, d8, d9};
/*
    prints char airspace matrix for each drone mvmnt
    'A' represents airport - starting position
    'D' represents destination
*/
void outputAirspace() {
    int i, j;

    airspace[d0.airport_x][d0.airport_y]='A';
    airspace[d1.airport_x][d1.airport_y]='A';
    airspace[d2.airport_x][d2.airport_y]='A';
    airspace[d3.airport_x][d3.airport_y]='A';
    airspace[d4.airport_x][d4.airport_y]='A';
    airspace[d5.airport_x][d5.airport_y]='A';
    airspace[d6.airport_x][d6.airport_y]='A';
    airspace[d7.airport_x][d7.airport_y]='A';
    airspace[d8.airport_x][d8.airport_y]='A';
    airspace[d9.airport_x][d9.airport_y]='A';

    airspace[d0.change_x][d0.change_y]='D';
    airspace[d1.change_x][d1.change_y]='D';
    airspace[d2.change_x][d2.change_y]='D';
    airspace[d3.change_x][d3.change_y]='D';
    airspace[d4.change_x][d4.change_y]='D';
    airspace[d5.change_x][d5.change_y]='D';
    airspace[d6.change_x][d6.change_y]='D';
    airspace[d7.change_x][d7.change_y]='D';
    airspace[d8.change_x][d8.change_y]='D';
    airspace[d9.change_x][d9.change_y]='D';

    pthread_mutex_lock(&mtx);
    for (i = 0; i < 5 * NUM_DRONES; i++ ) {
        for (j = 0; 5 * NUM_DRONES; j++) {
            printf("%c", airspace[i][j]);
        }
        //escape buffer
        printf('\n');
    }
    pthread_mutex_unlock(&mtx);
}

void omgCollision(int i, int j){
	pthread_mutex_lock(&mtx);
	airspace[i][j]='&';
	pthread_mutex_unlock(&mtx);
	sleep(1);
	system("clear");
	outputAirspace();
}


/* 
   checkClearAirspace 
   @return type bool
   @param int reference x -> x grid location
   @param int reference y -> y grid location
   Check airspace around drone for collisions
*/

bool checkClearAirspace(int x, int y) {
   if ((x < 50 || x > 1) && (y < 50 || y > 1)
      && airspace[x][y] !='!' && airspace[x][y]!='&'
      && airspace[x][y]!='+') {
      return true;
   }
   return false;
}

int main() {
    pthread_t threads[NUM_DRONES];
    int i, j;

    void* status;
    pthread_attr_t attr;

    pthread_mutex_init(&mtx, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < NUM_DRONES; i++) {
        pthread_create(&threads[i],NULL,outputAirspace,(void *)i);
    }

    }