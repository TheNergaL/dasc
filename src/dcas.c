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

struct thread_data{
  int thread_id;
  int airport_x,airport_y;
  int package_x,package_y;
};
struct thread_data thread_data_array[NUM_DRONES];

struct obstacles{
    int obs_x;
    int obs_y;
};
struct obstacles obstacle_array[NUM_OBSTACLES];

int main (int argc, char **argv)
{
  makeMap();
  placeObstacles();
  
  pthread_t threads[NUM_DRONES]; //Thread Address
  //int *taskids[NUM_DRONES];
  int retVal; //Holds thread return code
  long t; //Loop Counter
  for(t=0;t<NUM_DRONES;t++) {


    // TODO: add packages to be arbitrary
    int r1 = rand() % MAP_SIZE;
    int r2 = rand() % MAP_SIZE; //guarantee 2nd random won't be same as first
    thread_data_array[t].thread_id = t;
    thread_data_array[t].airport_x = t;
    thread_data_array[t].airport_y = t;
    thread_data_array[t].package_x = t+r1;
    thread_data_array[t].package_y = t+r2;

    retVal = pthread_create(&threads[t], NULL, fly, (void *) &thread_data_array[t]);
    if (retVal) {
      printf("ERROR: return code from pthread_create() is %d\n", retVal);
      exit(-1);
    }
  }
  pthread_exit(NULL);
}

void avoid(int* cx, int* cy, char direction, int taskid){
    
    if(direction == '>'){
            airspace[(*cx)++][(*cy)] = taskid;//down
            airspace[(*cx)][(*cy)++] = taskid;//right
            airspace[(*cx)][(*cy)++] = taskid;//right
            airspace[(*cx)--][(*cy)] = taskid;//up
             
    }
    if(direction == 'V'){
            airspace[(*cx)][(*cy)--] = taskid;//left
            airspace[(*cx)++][(*cy)] = taskid;//down
            airspace[(*cx)++][(*cy)] = taskid;//down
            airspace[(*cx)][(*cy)++] = taskid;//right
        
    }
    if(direction == '^'){
            airspace[(*cx)][(*cy)--] = taskid;//left
            airspace[(*cx)--][(*cy)] = taskid;//up
            airspace[(*cx)--][(*cy)] = taskid;//up
            airspace[(*cx)][(*cy)++] = taskid;//right
        
    }
    if(direction == '<'){
            airspace[(*cx)++][(*cy)] = taskid;//down
            airspace[(*cx)][(*cy)--] = taskid;//left
            airspace[(*cx)][(*cy)--] = taskid;//left
            airspace[(*cx)--][(*cy)] = taskid;//up
        
    }
}

// define x, y positions of obstacles and places them on the airspace
void placeObstacles(){
    obstacle_array[0].obs_x = 0;
    obstacle_array[0].obs_y = 5;
    obstacle_array[1].obs_x = 5;
    obstacle_array[1].obs_y = 10;
    obstacle_array[2].obs_x = 5;
    obstacle_array[2].obs_y = 15;
    obstacle_array[3].obs_x = 8;
    obstacle_array[3].obs_y = 14;
    
    for(int i = 0; i < NUM_OBSTACLES; i++){
        int x = obstacle_array[i].obs_x;
        int y = obstacle_array[i].obs_y;
        
        airspace[x][y]= 'X';
    }
}

void *fly(void *arg0){
  int taskid;
  int home_x, home_y;
  int pack_x, pack_y;
  struct thread_data *data;

  data = (struct thread_data *) arg0;
  taskid = data->thread_id;
  taskid += 48 ;
  home_x = data->airport_x;
  home_y = data->airport_y;
  pack_x = data->package_x;
  pack_y = data->package_y;
  
  airspace[home_x][home_y] = taskid;
  printMap();
  
  int curr_x = home_x;
  int curr_y = home_y;
  
  char direction = '>';
  for(;curr_y < pack_y; curr_y++ ){
      if(airspace[curr_x][curr_y+1] == 'X' || airspace[curr_x][curr_y+1] == '1' || airspace[curr_x][curr_y+1] == '2' 
      || airspace[curr_x][curr_y+1] == '3' || airspace[curr_x][curr_y+1] == '4' || airspace[curr_x][curr_y+1] == '5'
      || airspace[curr_x][curr_y+1] == '6' || airspace[curr_x][curr_y+1] == '7' || airspace[curr_x][curr_y+1] == '8'
      || airspace[curr_x][curr_y+1] == '9' || airspace[curr_x][curr_y+1] == '0'){
        avoid(&curr_x,&curr_y, direction, taskid);
      }
      airspace[curr_x][curr_y+1] = taskid;
      airspace[curr_x][curr_y] = direction;
      printMap();
      
      usleep(sleep_2);
      
  }
  
  direction = 'V';
  for(;curr_x < pack_x; curr_x++ ){
      if(airspace[curr_x+1][curr_y] == 'X' || airspace[curr_x+1][curr_y] == '1' || airspace[curr_x+1][curr_y] == '2'
      || airspace[curr_x+1][curr_y] == '3' || airspace[curr_x+1][curr_y] == '4' || airspace[curr_x+1][curr_y] == '5'
      || airspace[curr_x+1][curr_y] == '6' || airspace[curr_x+1][curr_y] == '7' || airspace[curr_x+1][curr_y] == '8'
      || airspace[curr_x+1][curr_y] == '9' || airspace[curr_x+1][curr_y] == '0'){
        avoid(&curr_x,&curr_y, direction, taskid);
      }
      airspace[curr_x+1][curr_y] = taskid;
      airspace[curr_x][curr_y] = direction;
      printMap();
      usleep(sleep_2);
      
  }
  
  direction = '^';
  for(;curr_x > home_x; curr_x-- ){ 
      if(airspace[curr_x-1][curr_y] =='X' || airspace[curr_x-1][curr_y] =='1' || airspace[curr_x-1][curr_y] =='2' 
      || airspace[curr_x-1][curr_y] =='3' || airspace[curr_x-1][curr_y] =='4' || airspace[curr_x-1][curr_y] =='5' 
      || airspace[curr_x-1][curr_y] =='6' || airspace[curr_x-1][curr_y] =='7' || airspace[curr_x-1][curr_y] =='8'
      || airspace[curr_x-1][curr_y] =='9' || airspace[curr_x-1][curr_y] =='0' ){
        avoid(&curr_x,&curr_y, direction, taskid);
      }
      airspace[curr_x-1][curr_y] = taskid;
      airspace[curr_x][curr_y] = direction;
      printMap();
      usleep(sleep_2);
      
  }
  
  direction = '<';
  for(;curr_y > home_y; curr_y-- ){
      if(airspace[curr_x][curr_y-1] == 'X' || airspace[curr_x][curr_y-1] == '1' || airspace[curr_x][curr_y-1] == '2'
      || airspace[curr_x][curr_y-1] == '3' || airspace[curr_x][curr_y-1] == '4'|| airspace[curr_x][curr_y-1] == '5'
      || airspace[curr_x][curr_y-1] == '6' || airspace[curr_x][curr_y-1] == '7'|| airspace[curr_x][curr_y-1] == '8'
      || airspace[curr_x][curr_y-1] == '9' || airspace[curr_x][curr_y-1] == '0'){
        avoid(&curr_x,&curr_y, direction, taskid);
      }
      airspace[curr_x][curr_y-1] = taskid;
      airspace[curr_x][curr_y] = direction;
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