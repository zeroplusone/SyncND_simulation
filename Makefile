CC = g++
CFLAGS = -std=c++11
OBJS = Event.o Node.o Group.o Parameter.o main.o 
PROG = SyncND.out

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

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

clean:
	rm *.o