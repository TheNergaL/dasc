all: output/map.o output/drone.o output/dcas.o jimmyhua_proj1

output/map.o: src/map.c include/map.h include/drone.h include/struct.h
	gcc -Iinclude/ -o output/map.o -c src/map.c -lpthread

output/drone.o: src/drone.c include/drone.h include/map.h include/struct.h
	gcc -Iinclude/ -o output/drone.o -c src/drone.c -lpthread

output/dcas.o: src/dcas.c include/map.h include/drone.h include/struct.h
	gcc -Iinclude/ -o output/dcas.o -c src/dcas.c -lpthread

jimmyhua_proj1: output/dcas.o output/map.o output/drone.o
	gcc -o jimmyhua_proj1 output/map.o output/drone.o output/dcas.o -lpthread