#ifndef MAP_H_
#define MAP_H_

#include "struct.h"

//all stubs defined in src/map.c

//Generate default map with x,y coord as base


Map createMap(int x, int y);
//Printes out map
void printMap(Map *m);
//Generate new drone passing in an id
Drone* orderDrone(Map *m,int id);
//Assign job to drone
void assignJob(Drone *d, Map *m);
//void assignJob(Drone *d, Map *m, int x, int y);
//Get a package
void getPackage(Drone *d);
//Assign destenation to base
void returnHome(Drone *d,Map *m);
//Check runway for lift
int requestTakeoff(Drone *d,Map *m);
//Check runway to land
int requestLand(Drone *d,Map *m);
//Generate random buildings on map
void createBuilding(Map *m,int count);
// void createBuilding(Map *m,int x,int y);
//Controls drone state and movement
void controlTower(Drone *d,Map * m);

#endif