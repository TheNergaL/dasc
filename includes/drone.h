#ifndef DRONE_H_
#define DRONE_H_

#include "struct.h"

//Sets drone state to standby
void standby(Drone *d);
//Allows drone to takeoff
void takeoff(Drone *d);
//Moves drone around map
int move(Drone *d,Map *m,int state);
//Drone has crashed
void collision(Drone *d);
//Drone reached destination and delivers
void deliver(Drone *d);
//Drone can land
void land(Drone *d,Map *m);

#endif // DRONE_H_