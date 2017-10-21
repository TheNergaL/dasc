#ifndef DRONE_H_
#define DRONE_H_

#include "struct.h"
//all stubs defined in src/drone.c

//Sets drone state to wait
void wait(Drone *d);
//Allows drone to lift
void lift(Drone *d);
//Moves drone around map
int move(Drone *d,Map *m, int state);
//Drone has crashed
void crash(Drone *d);
//Drone reached destination and delivers
void deliverySuccessful(Drone *d);
//Drone can comeHome
void comeHome(Drone *d,Map *m);

#endif // DRONE_H_