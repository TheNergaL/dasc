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

Drone d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;

/* 
   checkClearAirspace 
   @return type bool
   @param int reference x -> x grid location
   @param int reference y -> y grid location
   Check airspace around drone for collisions
*/

bool checkClearAirspace(int& x, int& y) {
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

    pthread_mutex_init(&count_mtx, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < NUM_DRONES; i++) {
        pthread_create(&threads[i],NULL,printDroneMap,(void *)t);
    }

    }

}
