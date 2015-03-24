CC=gcc
LINK=g++
CFLAGS=-I../xenomai/include  -I../lib_destijl/headers
OBJ=fonctions.o global.o main.o periodic_arena.o detection_arena.o thread_battery.o
OBJ_SRC=../lib_destijl/source/*.o
LIB= -lopencv_core -lopencv_highgui -lopencv_imgproc -lxenomai -lnative -L../xenomai/lib

all: main


main: $(OBJ) 						
	$(LINK) $(OBJ) $(OBJ_SRC) -o robot $(LIB)

thread_battery.o: thread_battery.c thread_battery.h
	$(CC) -g -Wall $(CFLAGS) -c thread_battery.c -o thread_battery.o

periodic_arena.o: periodic_arena.c periodic_arena.h
	$(CC) -g -Wall $(CFLAGS) -c periodic_arena.c -o periodic_arena.o

detection_arena.o: detection_arena.c detection_arena.h
	$(CC) -g -Wall $(CFLAGS) -c detection_arena.c -o detection_arena.o

fonctions.o: fonctions.c dmessage.o fonctions.h 
	$(CC) -g -Wall $(CFLAGS)  -c fonctions.c -o fonctions.o

global.o: global.c global.h
	$(CC) -g -Wall $(CFLAGS) -c global.c -o global.o


main.o: main.c global.h fonctions.h
	$(CC) -g -Wall $(CFLAGS) -c main.c -o main.o


dmessage.o: ../lib_destijl/source/dmessage.c ../lib_destijl/headers/dmessage.h ../lib_destijl/headers/dtools.h  
	cd ../lib_destijl/source; echo "entering source"; \
	$(CC) -g -Wall $(CFLAGS)  -c *.c
	cd ..

clean:
	rm -f $(OBJ) $(OBJ_SRC) robot
