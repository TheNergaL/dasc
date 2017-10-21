#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NUM_DRONES 10 
#define NUM_OBSTACLES 10 
#define MAP_SIZE 50

int sleep_2 = 200000;

char airspace[MAP_SIZE][MAP_SIZE];

void makeMap();
void printMap();
void *fly(void *arg0);
void placeObstacles();
void avoid(int*, int*, char, int);

struct threadData{
  int thread_id;
  int airport_x,airport_y;
  int package_x,package_y;
};
struct threadData threadDataArr[NUM_DRONES];

struct obstacles{
    int obs_x;
    int obs_y;
};
struct obstacles obsArr[NUM_OBSTACLES];

int main (int argc, char **argv)
{
  makeMap();
  placeObstacles();
  
  pthread_t threads[NUM_DRONES]; //Thread Address
  //int *taskids[NUM_DRONES];
  int retVal; //Holds thread return code
  long t; //Loop Counter
  for(t=0;t<NUM_DRONES;t++) {


    //drones all start at [1,1], [2,2], [3,3] ... [n,n]
    //all packages are located at arbitrary locations through the airspace
    int r1 = rand() % MAP_SIZE;
    int r2 = rand() % MAP_SIZE; 
    threadDataArr[t].thread_id = t;
    threadDataArr[t].airport_x = t;
    threadDataArr[t].airport_y = t;
    threadDataArr[t].package_x = t+r1;
    threadDataArr[t].package_y = t+r2;

    retVal = pthread_create(&threads[t], NULL, fly, (void *) &threadDataArr[t]);
    if (retVal) {
      printf("ERROR: return code from pthread_create() is %d\n", retVal);
      exit(-1);
    }
  }
  pthread_exit(NULL);
}

void avoid(int* currPosX, int* currPosY, char nextMove, int taskID){
    
    if(nextMove == '>'){
            airspace[(*currPosX)++][(*currPosY)] = taskID;//down
            airspace[(*currPosX)][(*currPosY)++] = taskID;//right
            airspace[(*currPosX)][(*currPosY)++] = taskID;//right
            airspace[(*currPosX)--][(*currPosY)] = taskID;//up
             
    }
    if(nextMove == 'V'){
            airspace[(*currPosX)][(*currPosY)--] = taskID;//left
            airspace[(*currPosX)++][(*currPosY)] = taskID;//down
            airspace[(*currPosX)++][(*currPosY)] = taskID;//down
            airspace[(*currPosX)][(*currPosY)++] = taskID;//right
        
    }
    if(nextMove == '^'){
            airspace[(*currPosX)][(*currPosY)--] = taskID;//left
            airspace[(*currPosX)--][(*currPosY)] = taskID;//up
            airspace[(*currPosX)--][(*currPosY)] = taskID;//up
            airspace[(*currPosX)][(*currPosY)++] = taskID;//right
        
    }
    if(nextMove == '<'){
            airspace[(*currPosX)++][(*currPosY)] = taskID;//down
            airspace[(*currPosX)][(*currPosY)--] = taskID;//left
            airspace[(*currPosX)][(*currPosY)--] = taskID;//left
            airspace[(*currPosX)--][(*currPosY)] = taskID;//up
        
    }
}

// define x, y positions of obstacles and places them on the airspace
void placeObstacles(){
    obsArr[0].obs_x = 0;
    obsArr[0].obs_y = 5;
    obsArr[1].obs_x = 5;
    obsArr[1].obs_y = 10;
    obsArr[2].obs_x = 5;
    obsArr[2].obs_y = 15;
    obsArr[3].obs_x = 8;
    obsArr[3].obs_y = 14;
    
    for(int i = 0; i < NUM_OBSTACLES; i++){
        int x = obsArr[i].obs_x;
        int y = obsArr[i].obs_y;
        
        airspace[x][y]= 'X';
    }
}

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

void printMap(){
	for(int i = 0; i < MAP_SIZE; i++){
		for (int j = 0; j < MAP_SIZE; j++){
			printf("%c", airspace[i][j]);
		}
		printf("\n");
	}
	return;
}

void makeMap(){
    for (int i = 0; i < MAP_SIZE; i++){
		for (int j = 0; j < MAP_SIZE; j++){
			airspace[i][j] = '.';
		}
	}

	return;
}