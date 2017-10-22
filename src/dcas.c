#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

//preproccesor macros for defining vars
#define NUM_DRONES 10 
#define NUM_OBSTACLES 10 
#define MAP_SIZE 50

//sleep for 2 seconds
int sleep_2 = 200000;

//global mutex thread for locking and unlocking during collision avoidance
pthread_mutex_t mtx;

//2d char array of size 50*50 which holds drones, packages, airports and obstacles
char airspace[MAP_SIZE][MAP_SIZE];
//create the map
void makeMap();
//output map 
void printMap();
//fly function for passing into pthreads
void *fly(void *arg0);
//place obstacles arbitrarily on the map
void placeObstacles();
// check for obstacles (and other drones) for every movement iteration
// search for a different path to take
void avoid(int*, int*, char, int);

// contains thread number, airport location and package location for the drones
struct threadData{
  int thread_id;
  int airport_x,airport_y;
  int package_x,package_y;
};
// array of drones
struct threadData threadDataArr[NUM_DRONES];

// obstacle struct which defines x,y coords of obstacles on the map
struct obstacles{
    int obs_x;
    int obs_y;
};

// array of obstacles
struct obstacles obsArr[NUM_OBSTACLES];

int main (int argc, char **argv)
{
  makeMap();
  placeObstacles();
  
  pthread_mutex_init(&mtx, NULL);
  //make our pthreads
  pthread_t threads[NUM_DRONES]; 
  // check for pthreade create error returns
  int retVal; 
  // just a regular old loop var
  long t; 
  for(t=0;t<NUM_DRONES;t++) {


    //drones all start at [0,0], [1,1], [2,2], [3,3] ... [n,n]
    //all packages are located at arbitrary locations through the airspace
    int r1 = rand() % MAP_SIZE;
    int r2 = rand() % MAP_SIZE; 
    // initialize drones and packages
    threadDataArr[t].thread_id = t;
    threadDataArr[t].airport_x = t;
    threadDataArr[t].airport_y = t;
    threadDataArr[t].package_x = t+r1;
    threadDataArr[t].package_y = t+r2;
     
    // check for pthreade create errs
    retVal = pthread_create(&threads[t], NULL, fly, (void *) &threadDataArr[t]);
    if (retVal) {
      printf("ERROR: return code from pthread_create() is %d\n", retVal);
      exit(-1);
    }
  }
  // destroy mutex thread
  pthread_mutex_destroy(&mtx);
  // exit pthreads
  pthread_exit(NULL);
}

// function to make sure drone path is clear and if not, move drones to avoid collisions
// takes in the drone's current x,y possition, their next move to check, and a taskID which identifies the next move
void avoid(int* currPosX, int* currPosY, char nextMove, int taskID){
    
    if(nextMove == '>'){
            pthread_mutex_lock(&mtx);
            airspace[(*currPosX)++][(*currPosY)] = taskID;//down
            airspace[(*currPosX)][(*currPosY)++] = taskID;//right
            airspace[(*currPosX)][(*currPosY)++] = taskID;//right
            airspace[(*currPosX)--][(*currPosY)] = taskID;//up
            pthread_mutex_unlock(&mtx);
    }
    if(nextMove == 'V'){
            pthread_mutex_lock(&mtx);
            airspace[(*currPosX)][(*currPosY)--] = taskID;//left
            airspace[(*currPosX)++][(*currPosY)] = taskID;//down
            airspace[(*currPosX)++][(*currPosY)] = taskID;//down
            airspace[(*currPosX)][(*currPosY)++] = taskID;//right
            pthread_mutex_unlock(&mtx);
    }
    if(nextMove == '^'){
            pthread_mutex_lock(&mtx);
            airspace[(*currPosX)][(*currPosY)--] = taskID;//left
            airspace[(*currPosX)--][(*currPosY)] = taskID;//up
            airspace[(*currPosX)--][(*currPosY)] = taskID;//up
            airspace[(*currPosX)][(*currPosY)++] = taskID;//right
            pthread_mutex_unlock(&mtx);
    }
    if(nextMove == '<'){
            pthread_mutex_lock(&mtx);
            airspace[(*currPosX)++][(*currPosY)] = taskID;//down
            airspace[(*currPosX)][(*currPosY)--] = taskID;//left
            airspace[(*currPosX)][(*currPosY)--] = taskID;//left
            airspace[(*currPosX)--][(*currPosY)] = taskID;//up
            pthread_mutex_unlock(&mtx);
    }
}

// define x, y positions of obstacles and places them on the airspace
// 
void placeObstacles(){
    int obsx_r1 = rand() % MAP_SIZE;
    int obsy_r1 = rand() % MAP_SIZE;
    int obsx_r2 = rand() % MAP_SIZE;
    int obsy_r2 = rand() % MAP_SIZE;
    int obsx_r3 = rand() % MAP_SIZE;
    int obsy_r3 = rand() % MAP_SIZE;
    int obsx_r4 = rand() % MAP_SIZE;
    int obsy_r4 = rand() % MAP_SIZE;
    int obsx_r5 = rand() % MAP_SIZE;
    int obsy_r5 = rand() % MAP_SIZE;
    int obsx_r6 = rand() % MAP_SIZE;
    int obsy_r6 = rand() % MAP_SIZE;
    int obsx_r7 = rand() % MAP_SIZE;
    int obsy_r7 = rand() % MAP_SIZE;
    int obsx_r8 = rand() % MAP_SIZE;
    int obsy_r8 = rand() % MAP_SIZE;
    // keep 0 and 1 static for demo purposes
    obsArr[0].obs_x = 0;
    obsArr[0].obs_y = 5;
    obsArr[1].obs_x = 5;
    obsArr[1].obs_y = 10;
    obsArr[2].obs_x = obsx_r1;
    obsArr[2].obs_y = obsy_r1;
    obsArr[3].obs_x = obsx_r2;
    obsArr[3].obs_y = obsy_r2;
    obsArr[4].obs_x = obsx_r3;
    obsArr[4].obs_y = obsy_r3;
    obsArr[5].obs_x = obsx_r4;
    obsArr[5].obs_y = obsy_r4;
    obsArr[6].obs_x = obsx_r5;
    obsArr[6].obs_y = obsy_r5;
    obsArr[7].obs_x = obsx_r6;
    obsArr[7].obs_y = obsy_r6;
    obsArr[8].obs_x = obsx_r7;
    obsArr[8].obs_y = obsy_r7;
    obsArr[9].obs_x = obsx_r8;
    obsArr[9].obs_y = obsy_r8;
    
    for(int i = 0; i < NUM_OBSTACLES; i++){
        int x = obsArr[i].obs_x;
        int y = obsArr[i].obs_y;
        
        airspace[x][y]= 'X';
    }
}
//usleep (microsleep) used in this function for map reprinting isn't too fast to see
// this function gets passed in as the third argument in pthread_create
// initializes drones in the airspace and assigns them an ascii value
// iterates drones through the map to their package location and then sends them home
// avoiding collisions and reprinting the map with each iteration.

void *fly(void *arg0){
  int taskID;
  int home_x, home_y;
  int pack_x, pack_y;
  struct threadData *data;

  data = (struct threadData *) arg0;
  taskID = data->thread_id;
  taskID += 48 ; //ASCII 0 = 'drone' #1, ASCII 1 (49) = 'drone' #2,  etc
  home_x = data->airport_x;
  home_y = data->airport_y;
  pack_x = data->package_x;
  pack_y = data->package_y;
  
  airspace[home_x][home_y] = taskID;
  printMap();
  
  int curr_x = home_x;
  int curr_y = home_y;
  
  char nextMove = '>';
  for(;curr_y < pack_y; curr_y++ ){
      if(airspace[curr_x][curr_y+1] == 'X' || airspace[curr_x][curr_y+1] == '1' || airspace[curr_x][curr_y+1] == '2' 
      || airspace[curr_x][curr_y+1] == '3' || airspace[curr_x][curr_y+1] == '4' || airspace[curr_x][curr_y+1] == '5'
      || airspace[curr_x][curr_y+1] == '6' || airspace[curr_x][curr_y+1] == '7' || airspace[curr_x][curr_y+1] == '8'
      || airspace[curr_x][curr_y+1] == '9' || airspace[curr_x][curr_y+1] == '0'){
        avoid(&curr_x,&curr_y, nextMove, taskID);
      }
      airspace[curr_x][curr_y+1] = taskID;
      airspace[curr_x][curr_y] = nextMove;
      printMap();
      
      usleep(sleep_2);
      
  }
  
  nextMove = 'V';
  for(;curr_x < pack_x; curr_x++ ){
      if(airspace[curr_x+1][curr_y] == 'X' || airspace[curr_x+1][curr_y] == '1' || airspace[curr_x+1][curr_y] == '2'
      || airspace[curr_x+1][curr_y] == '3' || airspace[curr_x+1][curr_y] == '4' || airspace[curr_x+1][curr_y] == '5'
      || airspace[curr_x+1][curr_y] == '6' || airspace[curr_x+1][curr_y] == '7' || airspace[curr_x+1][curr_y] == '8'
      || airspace[curr_x+1][curr_y] == '9' || airspace[curr_x+1][curr_y] == '0'){
        avoid(&curr_x,&curr_y, nextMove, taskID);
      }
      airspace[curr_x+1][curr_y] = taskID;
      airspace[curr_x][curr_y] = nextMove;
      printMap();
      usleep(sleep_2);
      
  }
  
  nextMove = '^';
  for(;curr_x > home_x; curr_x-- ){ 
      if(airspace[curr_x-1][curr_y] =='X' || airspace[curr_x-1][curr_y] =='1' || airspace[curr_x-1][curr_y] =='2' 
      || airspace[curr_x-1][curr_y] =='3' || airspace[curr_x-1][curr_y] =='4' || airspace[curr_x-1][curr_y] =='5' 
      || airspace[curr_x-1][curr_y] =='6' || airspace[curr_x-1][curr_y] =='7' || airspace[curr_x-1][curr_y] =='8'
      || airspace[curr_x-1][curr_y] =='9' || airspace[curr_x-1][curr_y] =='0' ){
        avoid(&curr_x,&curr_y, nextMove, taskID);
      }
      airspace[curr_x-1][curr_y] = taskID;
      airspace[curr_x][curr_y] = nextMove;
      printMap();
      usleep(sleep_2);
      
  }
  
  nextMove = '<';
  for(;curr_y > home_y; curr_y-- ){
      if(airspace[curr_x][curr_y-1] == 'X' || airspace[curr_x][curr_y-1] == '1' || airspace[curr_x][curr_y-1] == '2'
      || airspace[curr_x][curr_y-1] == '3' || airspace[curr_x][curr_y-1] == '4'|| airspace[curr_x][curr_y-1] == '5'
      || airspace[curr_x][curr_y-1] == '6' || airspace[curr_x][curr_y-1] == '7'|| airspace[curr_x][curr_y-1] == '8'
      || airspace[curr_x][curr_y-1] == '9' || airspace[curr_x][curr_y-1] == '0'){
        avoid(&curr_x,&curr_y, nextMove, taskID);
      }
      airspace[curr_x][curr_y-1] = taskID;
      airspace[curr_x][curr_y] = nextMove;
      printMap();
      usleep(sleep_2);
      
  }
  pthread_exit(NULL);
}

// prints character map by printing each index in airspace
void printMap(){
	for(int i = 0; i < MAP_SIZE; i++){
		for (int j = 0; j < MAP_SIZE; j++){
			printf("%c", airspace[i][j]);
		}
		printf("\n");
	}
	return;
}

// initializes the map as just 50x50 '.'s 
void makeMap(){
    for (int i = 0; i < MAP_SIZE; i++){
		for (int j = 0; j < MAP_SIZE; j++){
			airspace[i][j] = '.';
		}
	}

	return;
}