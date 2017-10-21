#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NUM_DRONES 10 
#define NUM_OBSTACLES 10 
#define LENGTH 50

int sleep_time = 200000;

char grid[LENGTH][LENGTH];

void create_grid();
void print_grid();
void *fly(void *threadarg);
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
  create_grid();
  placeObstacles();
  
  pthread_t threads[NUM_DRONES]; //Thread Address
  //int *taskids[NUM_DRONES];
  int retVal; //Holds thread return code
  long t; //Loop Counter
  for(t=0;t<NUM_DRONES;t++) {


    // TODO: add packages to be arbitrary
    int r1 = rand() % LENGTH;
    int r2 = rand() % LENGTH - r1; //guarantee 2nd random won't be same as first
    thread_data_array[t].thread_id = t;
    thread_data_array[t].airport_x = t;
    thread_data_array[t].airport_y = t;
    if (r1 != r2) {
    thread_data_array[t].package_x = t+r1;
    thread_data_array[t].package_y = t+r2;
    }
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
            grid[(*cx)++][(*cy)] = taskid;//down
            grid[(*cx)][(*cy)++] = taskid;//right
            grid[(*cx)][(*cy)++] = taskid;//right
            grid[(*cx)--][(*cy)] = taskid;//up
             
    }
    if(direction == 'V'){
            grid[(*cx)][(*cy)--] = taskid;//left
            grid[(*cx)++][(*cy)] = taskid;//down
            grid[(*cx)++][(*cy)] = taskid;//down
            grid[(*cx)][(*cy)++] = taskid;//right
        
    }
    if(direction == '^'){
            grid[(*cx)][(*cy)--] = taskid;//left
            grid[(*cx)--][(*cy)] = taskid;//up
            grid[(*cx)--][(*cy)] = taskid;//up
            grid[(*cx)][(*cy)++] = taskid;//right
        
    }
    if(direction == '<'){
            grid[(*cx)++][(*cy)] = taskid;//down
            grid[(*cx)][(*cy)--] = taskid;//left
            grid[(*cx)][(*cy)--] = taskid;//left
            grid[(*cx)--][(*cy)] = taskid;//up
        
    }
}

// define x, y positions of obstacles and places them on the grid
void placeObstacles(){
    obstacle_array[0].obs_x = 0;
    obstacle_array[0].obs_y = 5;
    obstacle_array[1].obs_x = 5;
    obstacle_array[1].obs_y = 10;
    
    for(int i = 0; i < NUM_OBSTACLES; i++){
        int x = obstacle_array[i].obs_x;
        int y = obstacle_array[i].obs_y;
        
        grid[x][y]= 'X';
    }
}

void *fly(void *threadarg){
  int taskid;
  int start_x, start_y;
  int dest_x, dest_y;
  struct thread_data *my_data;

  my_data = (struct thread_data *) threadarg;
  taskid = my_data->thread_id;
  taskid += 48 ;
  start_x = my_data->airport_x;
  start_y = my_data->airport_y;
  dest_x = my_data->package_x;
  dest_y = my_data->package_y;
  
  grid[start_x][start_y] = taskid;
  print_grid();
  
  int curr_x = start_x;
  int curr_y = start_y;
  
  char direction = '>';
  for(;curr_y < dest_y; curr_y++ ){
      if(grid[curr_x][curr_y+1] == 'X'){
        avoid(&curr_x,&curr_y, direction, taskid);
      }
      grid[curr_x][curr_y+1] = taskid;
      grid[curr_x][curr_y] = direction;
      print_grid();
      
      usleep(sleep_time);
      
  }
  
  direction = 'V';
  for(;curr_x < dest_x; curr_x++ ){
      if(grid[curr_x+1][curr_y] == 'X'){
        avoid(&curr_x,&curr_y, direction, taskid);
      }
      grid[curr_x+1][curr_y] = taskid;
      grid[curr_x][curr_y] = direction;
      print_grid();
      usleep(sleep_time);
      
  }
  
  direction = '^';
  for(;curr_x > start_x; curr_x-- ){ 
      if(grid[curr_x-1][curr_y] =='X'){
        avoid(&curr_x,&curr_y, direction, taskid);
      }
      grid[curr_x-1][curr_y] = taskid;
      grid[curr_x][curr_y] = direction;
      print_grid();
      usleep(sleep_time);
      
  }
  
  direction = '<';
  for(;curr_y > start_y; curr_y-- ){
      if(grid[curr_x][curr_y-1] == 'X'){
        avoid(&curr_x,&curr_y, direction, taskid);
      }
      grid[curr_x][curr_y-1] = taskid;
      grid[curr_x][curr_y] = direction;
      print_grid();
      usleep(sleep_time);
      
  }
  pthread_exit(NULL);
}

void print_grid(){
	for(int i = 0; i < LENGTH; i++){
		for (int j = 0; j < LENGTH; j++){
			printf("%c", grid[i][j]);
		}
		printf("\n");
	}
	return;
}

void create_grid(){
    for (int i = 0; i < LENGTH; i++){
		for (int j = 0; j < LENGTH; j++){
			grid[i][j] = '.';
		}
	}

	return;
}