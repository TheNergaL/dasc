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

void avoidCollision(int i, int j, int x, int y){
	char s;
	s='+';
	//for the case where the home position vertical coordinate is less than destination position vertical coordinate
	if(j<y){
			//check if the block of space upwards is open or not
			if(checkClearAirspace(i-1,j)){
					//move vertical upwards one time
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i--;	
					
					//move horizontal right one time
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=' ';
					pthread_mutex_unlock(&mtx);
					j++;	

					//move horizontal right one time
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=' ';
					pthread_mutex_unlock(&mtx);
					j++;	

					//move vertical downwards one time
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i++;	
					
			}else{
					//if block of space upwards is not open, move vertically downwards one time
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i++;	
					
					//move horizontal right one time
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=' ';
					pthread_mutex_unlock(&mtx);
					j++;	

					//move horizontal right one time
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=' ';
					pthread_mutex_unlock(&mtx);
					j++;	

					//move vertical upwards one time 
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i--;	
				
			}	
		//successfully avoided collision!
		return;				
	}
	//for the case where the home position vertical coordinate is more than destination position vertical coordinate
	if(j>y){
			//check if the block of space upwards is open or not
			if(checkClearAirspace(i-1,j)){
					//move vertically upwards one time
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=s;	
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i--;	

					//move horizonal left one time
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=' ';
					pthread_mutex_unlock(&mtx);
					j--;	

					//move horizontal left one time
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=' ';
					pthread_mutex_unlock(&mtx);
					j--;	

					//move vertically downwards one time
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i++;	
	
			}else{
					//if block of space upwards is not open move vertically downwards one time
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=s;	
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i++;	

					//move horizontal left one time
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=' ';
					pthread_mutex_unlock(&mtx);
					j--;	

					//move horizontal left one time
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=' ';
					pthread_mutex_unlock(&mtx);
					j--;	

					//move vertically upwards one time
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i--;	
						
			}
		//collision succesfully avoided!
		return;
	}
	//for the case where the home position horizontal coordinate is less than destination position horizontal coordinate 
	if(i<x){
			//check if the block of space on the left is open or not
			if(checkClearAirspace(i,j-1)){
					//move horizontal left one time
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=' ';
					pthread_mutex_unlock(&mtx);
					j--;	

					//move vertical downwards one time
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i++;	

					//move vertical downwards one time
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i++;

					//move horizontal right one time
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=' ';
					pthread_mutex_unlock(&mtx);
					j++;

			}else{
					//if the block of space on left is not open move right
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=' ';
					pthread_mutex_unlock(&mtx);
					j++;	

					//move vertical downwards one time
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i++;	

					//move vertical downwards one time
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i+1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i++;

					//move horizontal left one time
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=' ';
					pthread_mutex_unlock(&mtx);
					j--;
				
			}
		//succesfully avoided collision!
		return;
	
	}
	//for the case where the home position horizontal coordinate is more than destination position horizontal coordinate 
	if(i>x){
				//check if the block of space on the right is open or not
				if(checkClearAirspace(i,j+1)){
					//move horizontal right one time
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=' ';
					pthread_mutex_unlock(&mtx);
					j++;	

					//move vertical upwards one time
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i--;	

					//move vertical upwards one time
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i--;	

					//move horizontal left one time
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=' ';
					pthread_mutex_unlock(&mtx);
					j--;	

				}else{
					//if the block of space on right is not open move left one time
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j-1]=' ';
					pthread_mutex_unlock(&mtx);
					j--;	

					//move vertical upwards one time
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i--;	

					//move vertically upwards one time
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i-1][j]=' ';
					pthread_mutex_unlock(&mtx);
					i--;	

					//move horizontal right one time
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=s;
					pthread_mutex_unlock(&mtx);
					system("clear");
					outputAirspace();
					sleep(1);
					pthread_mutex_lock(&mtx);
					airspace[i][j+1]=' ';
					pthread_mutex_unlock(&mtx);
					j++;	

			}
		//successfully avoided collision!
		return;
	}

}

void moveDrone(int i, int j, int x, int y){
	char s;
	s='+';
	//while the vertical coordinates of drone and destination are not equal
	while(j!=y){
		//for the case where the drone position vertical coordinate is less than destination postion vertical coordinate 
		if((j<y)){
			//check if the block of space on the right is open or not
			if(checkClearAirspace(i,j+1)){	
				//move right one time
				pthread_mutex_lock(&mtx);
				airspace[i][j+1]=s; 
				pthread_mutex_unlock(&mtx);
				//sleep(1);
				system("clear");
				outputAirspace();
				sleep(1);
				pthread_mutex_lock(&mtx);
				airspace[i][j+1]=' ';
				pthread_mutex_unlock(&mtx);
				j++;

			}else{
				//if space on the right is occupied avoid collision or signal collision taking place 
				avoidCollision(i,j,x,y);
			//	omgCollision(i,j+1);
				j=j+2;
			}
					
		}
		//for the case where the drone position vertical coordinate is more than destination position vertical coordinate
		if((j>y)){
			//check if the block of space on the left is open or not
			if(checkClearAirspace(i,j-1)){
				//move left one time
				pthread_mutex_lock(&mtx);
				airspace[i][j-1]=s;
				pthread_mutex_unlock(&mtx);
				//sleep(1);
				system("clear");
				outputAirspace();
				sleep(1);
				pthread_mutex_lock(&mtx);
				airspace[i][j-1]=' ';
				pthread_mutex_unlock(&mtx);
				j--;

			}else{
				//if the space on the left is occupied avoid collision or signal collision taking place
				avoidCollision(i,j,x,y);
			//	omgCollision(i,j-1);
				j=j-2;
			}
		}
	}
	//while the horizontal coordinates of the drone and destination are not equal
	while(i!=x){
		//for the case where the drone position horizontal coordinate is less than destination position horizontal coordinate
		if((i<x)){
			//check if the block of space downwards is open or not
			if(checkClearAirspace(i+1,j)){
				//move downwards one time
				pthread_mutex_lock(&mtx);
				airspace[i+1][j]=s;	
				pthread_mutex_unlock(&mtx);
				//sleep(1);
				system("clear");
				outputAirspace();
				sleep(1);
				pthread_mutex_lock(&mtx);
				airspace[i+1][j]=' ';
				pthread_mutex_unlock(&mtx);
				i++;

			}else{
				//if the space downwards is occupied avoid collision or signal collision taking place
				avoidCollision(i,j,x,y);
			//	omgCollision(i+1,j);
				i=i+2;
			}
		}	
		//for the case where the drone position horizontal coordinate is more than destination position horizontal coordinate
		if((i>x)){
			//check if the block of space upwards is open or not
			if(checkClearAirspace(i-1,j)){
				//move upwards one time
				pthread_mutex_lock(&mtx);
				airspace[i-1][j]=s;
				pthread_mutex_unlock(&mtx);
				//sleep(1);
				system("clear");
				outputAirspace();
				sleep(1);
				pthread_mutex_lock(&mtx);
				airspace[i-1][j]=' ';
				pthread_mutex_unlock(&mtx);
				i--;

			}else{
				//if the space upwards is occupied avoid collision or signal collision taking place
				avoidCollision(i,j,x,y);
			//	omgCollision(i-1,j);
				i=i-2;
			}
		}
	}

}

void fillMap(int a, int b, int x, int y){
	
	pthread_mutex_lock(&mtx);
	int i,j;
	for(i=1;i<=50;i++){
		for(j=1;j<=50;j++){
		
			if(i!=50 && i!=1 && j !=50 && j!=1){
				airspace[i][j]=' ';
			}else{
				airspace[i][j]='x';
			}
		
		}
	
	}
	
	airspace[14][9]='!';
	airspace[28][39]='!';
	pthread_mutex_unlock(&mtx);
	//the moveDrone or navigation method is called here 2 times for the drone to first move from home to destination and then back to home
	moveDrone(a,b,x,y);
	moveDrone(x,y,a,b);
}

void *printDroneX(void *threadid){
	d0.hx=25;
	d0.hy=25;
	d0.dx=9;
	d0.dy=9;
	d1.hx=25;
	d1.hy=25;
	d1.dx=9;
	d1.dy=9;
	d2.hx=25;
	d2.hy=25;
	d2.dx=39;
	d2.dy=39;
	d3.hx=25;
	d3.hy=25;
	d3.dx=39;
	d3.dy=39;
	d4.hx=25;
	d4.hy=25;
	d4.dx=9;
	d4.dy=39;
	d5.hx=25;
	d5.hy=25;
	d5.dx=9;
	d5.dy=39;
	d6.hx=25;
	d6.hy=25;
	d6.dx=39;
	d6.dy=39;
	d7.hx=25;
	d7.hy=25;
	d7.dx=39;
	d7.dy=9;
	d8.hx=25;
	d8.hy=25;
	d8.dx=39;
	d8.dy=9;
	d9.hx=25;
	d9.hy=25;
	d9.dx=39;
	d9.dy=9;


	long tid;
	tid = (long)threadid;
	if(tid==0){
		fillMap(d0.hx, d0.hy, d0.dx, d0.dy);
	}
	if(tid==1){
		fillMap(d1.hx, d1.hy, d1.dx, d1.dy);
	}
	if(tid==2){
		fillMap(d2.hx, d2.hy, d2.dx, d2.dy);
	}
	if(tid==3){
		fillMap(d3.hx, d3.hy, d3.dx, d3.dy);
	}
	if(tid==4){
		fillMap(d4.hx, d4.hy, d4.dx, d4.dy);
	}
	if(tid==5){
		fillMap(d5.hx, d5.hy, d5.dx, d5.dy);
	}
	if(tid==6){
		fillMap(d6.hx, d6.hy, d6.dx, d6.dy);
	}
	if(tid==7){
		fillMap(d7.hx, d7.hy, d7.dx, d7.dy);
	}
	if(tid==8){
		fillMap(d8.hx, d8.hy, d8.dx, d8.dy);
	}
	if(tid==9){
		fillMap(d9.hx, d9.hy, d9.dx, d9.dy);
	}
	pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
	int rc;
	long t=0;
	long t1=1;
	long t2=2;
	long t3=3;
	long t4=4;
	long t5=5;
	long t6=6;
	long t7=7;
	long t8=8;
	long t9=9;

	void *status;
	pthread_attr_t attr;

	pthread_mutex_init(&mtx,NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	int i;
	for(t=0; t<NUM_THREADS;t++){
		pthread_create(&threads[t],NULL,printDroneX,(void *)t);
		sleep(2);
	}
		pthread_attr_destroy(&attr);
//		int i;
		for(i=0;i<NUM_THREADS;i++){
			pthread_join(threads[i],&status);
		}
	pthread_mutex_destroy(&mtx);
	pthread_exit(NULL);

}