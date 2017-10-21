all: output/map.o output/drone.o output/dcas.o tuckerpo_proj1

output/map.o: src/map.c includes/map.h includes/drone.h includes/struct.h
	gcc -Iinclude/ -o output/map.o -c src/map.c -lpthread

output/drone.o: src/drone.c includes/drone.h includes/map.h includes/struct.h
	gcc -Iinclude/ -o output/drone.o -c src/drone.c -lpthread

output/dcas.o: src/dcas.c includes/map.h includes/drone.h includes/struct.h
	gcc -Iinclude/ -o output/dcas.o -c src/dcas.c -lpthread

tuckerpo_proj1: output/dcas.o output/map.o output/drone.o
	gcc -o tuckerpo_proj1 output/map.o output/drone.o output/dcas.o -lpthread