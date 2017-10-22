CSE321 Lab 1 DASC.c Tucker Polomik 
------------------------------------------------------   
Lab work done for CSE321 Realtime and Embedded Systems
Language : C
Dependencies : C99/GNU99 (for -lpthread)
The goal of this lab is to create an abstract drone collision avoidance program,simulating a real-time embedded system making use of parallelism, multi-threading and concurrency in the C language.   

To build and run it on *nix systems: 
Open terminal & navigate to the 'dcas' directory 
Once in the dcas directory, type 'make' and the project will be built to 'tuckerpo_proj1' output file
./tuckerpo_proj1

Since POSIX threads are not native to Windows, you must run this program in mingw64 bash shell.
In the bash shell, in the dasc directory, type 'gcc -std=c99 dcas.c -o dcas.exe -lpthread'
This will envoke the GNU C Compiler with the C99 standarad on your .c file, linking the pthread library for building, and create 
and executable called dcas.exe, which can then be run.

Alternatively just run the *nix shell script I've included here by navigating to the dcas directory and typing ./capture into the terminal.

*Note: I know the output is kinda ugly. There are 10 drones that are created sequentially at [0,0], [1,1], [2,2], ... etc

The drones are represented by their pthread numbers, 0, 1, 2....

Upon instantiation, each drone is assigned a package to pick up arb0itrarily. These are represented by the apex of the drone's flight path (the position
where the drone turns around to come back home.) 

There are also obstacles for the done to avoid printed randomly about the map, represented by char 'X'

The drones will navigate to their respective packages avoiding obstacles and other drones along the way. Before each movement, the drone looks ahead
to it's next X and Y coordinate moves to ensure there are no obstacles or other drones in the way. If there are, it searches for the nearest clear path to take 
to it's package. If there are none, it will hover in place until a path opens.


Each drone has a trail of 'arrows' showing it's movement path. If drones avoid an obstacle or another drone, their 'ghosts' are left in place.

Example: Drone #5 is coming home and avoids an obstacle X will look like this: 

5<<<<X5<<<<
    ^<<


This represents the 5 drone coming back, finding the obstacle, and avoiding it by going under. Drones avoiding other drones however will just look like a mish
mash of numbers which is hard to make sense of. You can check that all drones succesfully obtained their packages and returned home without crashing 
by seeing that they've all returned back to their starting positions.

Output best viewed in a full-screen terminal window.

*Note #2: Sometimes, very rarely, the program segfaults while the drones are returning home. 
If this occurs please make clean and rebuild the program and run it again. Happy grading.
