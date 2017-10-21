#ifndef STRUCT_H_
#define STRUCT_H_

#include <pthread.h>

#define SIZE 51

typedef struct Coord{
	int point[2];   //[0] == x && [1] == y
} Coord;

typedef struct Box{
	Coord coord;    						//Box's coordinate
	int drone;      						//Number of Drones, mainly for base count
	int id;         						//Drone id
	int dest;								//Cood is a destination
	char item;   							//' ' if nothing,'x' if runway,'X' if destination, '+' if building, '^' if drone
	int locked;     						//Box currently being used.
	pthread_mutex_t mutexLock;				//lock box for drone;
} Box;

typedef struct Drone{
	int id;         						//Drones id
	Coord currLocation,destLocation;        //Current and destination location
	int state;      						//State drone is in
	int speed;      						//Speed the drone moves
	int delivered;  						//Is package delivered?
	int package;    						//Does drone have a package?
	int avoid;								//Direction it moved from
	int avoid2;								//Direction it moved two steps ago
	int move;								//Avoid repeats
} Drone;

typedef struct Map{
	Box grid[SIZE][SIZE];   				//Orignal grid
	Box* gridRow[SIZE];     				//Array of pointers to each row
	Box** map;              				//Pointer of pointers to orignal grid
	Coord base[5];          				//Center Base and runways
	int runway[4];          				//Is runway free?
	Drone* drones[250];       				//Stores drones
} Map;

typedef struct Keeper{
	Map *map;								//Map for thread
	Drone *drone;							//Drone for thread
	int count;							//Amount of drones
} Keeper;

#endif