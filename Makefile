CC = g++
CFLAGS = -std=c++11
DEBUG_CFLAGS = -std=c++11 -D DEBUG
OBJS = Event.o Parameter.o Node.o Group.o  main.o 
DEBUG_OBJS = DEBUG_Event.o DEBUG_Parameter.o DEBUG_Node.o DEBUG_Group.o  DEBUG_main.o 
PROG = SyncND.out

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

verbose: $(DEBUG_OBJS)
	$(CC) $(DEBUG_CFLAGS) -o verbose.out $(DEBUG_OBJS)

debug: $(OBJS)
	$(CC) $(CFLAGS) -g -o $(PROG).debug $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Parameter.o: Parameter.cpp
	$(CC) $(CFLAGS) -c Parameter.cpp

Group.o: Group.cpp
	$(CC) $(CFLAGS) -c Group.cpp

Node.o: Node.cpp
	$(CC) $(CFLAGS) -c Node.cpp

Event.o: Event.cpp
	$(CC) $(CFLAGS) -c Event.cpp

DEBUG_main.o: main.cpp
	$(CC) $(DEBUG_CFLAGS) -o DEBUG_main.o -c main.cpp

DEBUG_Parameter.o: Parameter.cpp
	$(CC) $(DEBUG_CFLAGS) -o DEBUG_Parameter.o -c Parameter.cpp

DEBUG_Group.o: Group.cpp
	$(CC) $(DEBUG_CFLAGS) -o DEBUG_Group.o -c Group.cpp

DEBUG_Node.o: Node.cpp
	$(CC) $(DEBUG_CFLAGS) -o DEBUG_Node.o -c Node.cpp

DEBUG_Event.o: Event.cpp
	$(CC) $(DEBUG_CFLAGS) -o DEBUG_Event.o -c Event.cpp

clean:
	rm *.o