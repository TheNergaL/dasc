CSE321 Lab 1 DASC.c 
----------------------------   
Lab work done for CSE321 Realtime and Embedded Systems
Language : C
Dependencies : C99/GNU99 (for -lpthread)
The goal of this lab is to create an abstract drone collision avoidance program,simulating a real-time embedded system making use of parallelism, multi-threading and concurrency in the C language.   

To build and run it on *nix systems: 
Open terminal & navigate to the 'dasc' directory (yes it's a typo)
Once in the dasc directory, type 'make' and the project will be built to 'tuckerpo_proj1' output file
./tuckerpo_proj1

Since POSIX threads are not native to Windows, you must run this program in mingw64 bash shell.
In the bash shell, in the dasc directory, type 'gcc -std=c99 dcas.c -o dcas.exe -lpthread'
This will envoke the GNU C Compiler with the C99 standarad on your .c file, linking the pthread library for building, and create 
and executable called dcas.exe, which can then be run.

Alternatively just run the shell script I've created here.